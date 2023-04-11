#include <ImGui_Yoga/YGNode_draw_recursive.hpp>

// -------------------------------------------------------------------------
// Constants

// Colors the same as on website (yogalayout.com)
ImGui_Yoga::YGNode_Draw_Style::YGNode_Draw_Style()
    : node_nonfocused_color( IM_COL32( 48,  56,  69,  51) ) // Semi-transmarent gray: rgba(48, 56, 69, 0.2)
    , node_focused_color   ( IM_COL32(107, 206, 187, 255) ) // Non-transparent  cyan: rgba(107, 206, 187, 1.0)

    , node_nonfocused_thickness( 1.0f )
    , node_focused_thickness   ( 2.0f )

    , position_offset_color( IM_COL32(115, 51, 205, 25) ) // Semi-transparent violet: rgba(115, 51, 205, 0.1)
    , margin_color         ( IM_COL32(214, 43,  28, 25) ) // Semi-transparent red:    rgba(214, 43, 28, 0.1)
    , border_color         ( IM_COL32(251, 170, 51, 38) ) // Semi-transparent yellow: rgba(251, 170, 51, 0.15)
    , padding_color        ( IM_COL32(123, 179, 41, 25) ) // Semi-transparent green:  rgba(123, 179, 41, 0.1)

    , values_color         ( IM_COL32(255, 255, 255, 127) ) // Semi-transparent white
{ }

static ImGui_Yoga::YGNode_Draw_Style DEFAULT_STYLE = {};

static constexpr size_t TEXT_BUFFER_SIZE = 32;
static char text_buffer[TEXT_BUFFER_SIZE];
static constexpr char FLOAT_FMT[] = "%0.1f";

// -------------------------------------------------------------------------
// Utility functions

namespace utils
{

inline float zero_if_nan(const float value)
{
    return YGFloatIsUndefined(value) ? 0.0f : value;
}

void draw_text_centered(ImDrawList* draw_list, const ImVec2& pos, ImU32 text_col, const char* text_begin, const char* text_end = nullptr)
{
    const ImVec2 text_size = ImGui::CalcTextSize(text_begin, text_end);
    const ImVec2 text_pos = {pos.x - (text_size.x / 2.0f), pos.y - (text_size.y / 2.0f) };

    draw_list->AddText(text_pos, text_col, text_begin, text_end);
}

inline ImVec2 rect_center(const ImVec2& topLeft, const ImVec2& botRight)
{
    return { (topLeft.x + botRight.x) / 2.0f, (topLeft.y + botRight.y) / 2.0f };
}

// via: https://stackoverflow.com/a/2412046/
int print_float_without_trailing_zeros(char* buffer, size_t buffer_size, float value)
{
    int count = snprintf(buffer, buffer_size, FLOAT_FMT, value);

    if(count > (int)buffer_size) {
        return count;
    }

    // Shift position, prior to '\0',
    count--;

    // Traverse from end to start, until not-zero, or (dot sign or comma) found
    while(buffer[count] == '0')
    {
        count--;

        if( (buffer[count] == '.') || (buffer[count] == ',') )
        {
            count--;
            break;
        }
    }

    buffer[count + 1] = '\0';
    return count + 1;
}

} // namespace utils

// -----------------------------------------------------------------------------

void ImGui_Yoga::YGNode_draw_recursive(
    YGNodeRef node,
    ImDrawList* draw_list,

    const ImVec2& origin,
    YGNodeConstRef focused_node,
    const YGNode_Draw_Style* style)
{
    if(node == nullptr)
    {
        return;
    }

    // -------------------------------------------------------------------------

    // If style not specified - use default
    if(style == nullptr)
    {
        style = &DEFAULT_STYLE;
    }

    // -------------------------------------------------------------------------
    // Extract node rect values

    const float left   = YGNodeLayoutGetLeft(node);
    const float top    = YGNodeLayoutGetTop(node);
    const float right  = YGNodeLayoutGetRight(node);
    const float bottom = YGNodeLayoutGetBottom(node);

    const float width  = YGNodeLayoutGetWidth(node);
    const float height = YGNodeLayoutGetHeight(node);

    // -------------------------------------------------------------------------

    // If width or height is undefined (nan) - it means 'YGNodeCalculateLayout()'
    // not called for that node -> node in 'undefined' state -> skip it
    if(YGFloatIsUndefined(width) || YGFloatIsUndefined(height))
        return;

    const bool is_focused = (node == focused_node);

    const ImVec2 node_rect__top_left  = {origin.x + left,         origin.y + top};
    const ImVec2 node_rect__bot_right = {origin.x + left + width, origin.y + top + height};

    // Draw node rect
    draw_list->AddRect(
                node_rect__top_left,  // p_min
                node_rect__bot_right, // p_max
                (is_focused ? style->node_focused_color : style->node_nonfocused_color), // col
                0.0f, // rounding
                0,    // flags
                (is_focused ? style->node_focused_thickness : style->node_nonfocused_thickness) // thickness
    );

    if(is_focused)
    {
        // ---------------------------------------------------------------------
        // Extract additional values

        const float margin_left   = YGNodeLayoutGetMargin(node, YGEdge::YGEdgeLeft);
        const float margin_top    = YGNodeLayoutGetMargin(node, YGEdge::YGEdgeTop);
        const float margin_right  = YGNodeLayoutGetMargin(node, YGEdge::YGEdgeRight);
        const float margin_bottom = YGNodeLayoutGetMargin(node, YGEdge::YGEdgeBottom);

        const float border_left   = YGNodeLayoutGetBorder(node, YGEdge::YGEdgeLeft);
        const float border_top    = YGNodeLayoutGetBorder(node, YGEdge::YGEdgeTop);
        const float border_right  = YGNodeLayoutGetBorder(node, YGEdge::YGEdgeRight);
        const float border_bottom = YGNodeLayoutGetBorder(node, YGEdge::YGEdgeBottom);

        const float padding_left   = YGNodeLayoutGetPadding(node, YGEdge::YGEdgeLeft);
        const float padding_top    = YGNodeLayoutGetPadding(node, YGEdge::YGEdgeTop);
        const float padding_right  = YGNodeLayoutGetPadding(node, YGEdge::YGEdgeRight);
        const float padding_bottom = YGNodeLayoutGetPadding(node, YGEdge::YGEdgeBottom);

        // ---------------------------------------------------------------------

        // Draw position offsets
        {
            /*
                Notices about 'position offsets' here:
                    - they are given from 'style', not from 'layout, since have
                      no idea how to get them
                    - if value units is 'percent' - it not displayed properly,
                      the same as on website (yogalayout.com) :)
             */

            float pos_offset_left   = YGUndefined;
            float pos_offset_top    = YGUndefined;
            float pos_offset_right  = YGUndefined;
            float pos_offset_bottom = YGUndefined;

            // Get values
            {
                {
                    const YGValue pos_all = YGNodeStyleGetPosition(node, YGEdge::YGEdgeAll);
                    if( YGFloatIsUndefined(pos_all.value) == false)
                    {
                        pos_offset_left   = pos_all.value;
                        pos_offset_top    = pos_all.value;
                        pos_offset_right  = pos_all.value;
                        pos_offset_bottom = pos_all.value;
                    }
                }

                {
                    const YGValue pos_horizontal = YGNodeStyleGetPosition(node, YGEdge::YGEdgeHorizontal);
                    if( YGFloatIsUndefined(pos_horizontal.value) == false)
                    {
                        if( YGFloatIsUndefined(pos_offset_left ) ) { pos_offset_left  = pos_horizontal.value; } // TODO: is it value or value/2 ?
                        if( YGFloatIsUndefined(pos_offset_right) ) { pos_offset_right = pos_horizontal.value; } // TODO: is it value or value/2 ?
                    }
                }

                {
                    const YGValue pos_vertical = YGNodeStyleGetPosition(node, YGEdge::YGEdgeVertical);
                    if( YGFloatIsUndefined(pos_vertical.value) == false)
                    {
                        if( YGFloatIsUndefined(pos_offset_top   ) ) { pos_offset_top    = pos_vertical.value; } // TODO: is it value or value/2 ?
                        if( YGFloatIsUndefined(pos_offset_bottom) ) { pos_offset_bottom = pos_vertical.value; } // TODO: is it value or value/2 ?
                    }
                }

                // TODO: maybe the next 4 cases must be:
                // if (value undefined)
                //    side_value = get value
                //    if(side_value not undefined)
                //       value = side_value
                // ????

                {
                    const YGValue pos_left = YGNodeStyleGetPosition(node, YGEdge::YGEdgeLeft);
                    if( YGFloatIsUndefined(pos_left.value) == false) {
                        if( YGFloatIsUndefined(pos_offset_left) ) { pos_offset_left = pos_left.value; }
                    }
                }

                {
                    const YGValue pos_top = YGNodeStyleGetPosition(node, YGEdge::YGEdgeTop);
                    if( YGFloatIsUndefined(pos_top.value) == false) {
                        if( YGFloatIsUndefined(pos_offset_top) ) { pos_offset_top = pos_top.value; }
                    }
                }

                {
                    const YGValue pos_right = YGNodeStyleGetPosition(node, YGEdge::YGEdgeRight);
                    if( YGFloatIsUndefined(pos_right.value) == false) {
                        if( YGFloatIsUndefined(pos_offset_right) ) { pos_offset_right = pos_right.value; }
                    }
                }

                {
                    const YGValue pos_bottom = YGNodeStyleGetPosition(node, YGEdge::YGEdgeBottom);
                    if( YGFloatIsUndefined(pos_bottom.value) == false) {
                        if( YGFloatIsUndefined(pos_offset_bottom) ) { pos_offset_bottom = pos_bottom.value; }
                    }
                }
            }

            // Draw offsets
            {
                if( !YGFloatIsUndefined(pos_offset_left) && (pos_offset_left != 0.0f) )
                {
                    ImVec2 pos_left__top_left  = {node_rect__top_left.x - pos_offset_left, node_rect__top_left.y};
                    ImVec2 pos_left__bot_right = {node_rect__top_left.x, node_rect__bot_right.y};

                    // Shift by margin
                    pos_left__top_left.x  -= utils::zero_if_nan(margin_left);
                    pos_left__bot_right.x -= utils::zero_if_nan(margin_left);

                    // Enlarve vertically to fill empty space, if margin is set
                    pos_left__top_left.y  -= utils::zero_if_nan(margin_top);
                    pos_left__bot_right.y += utils::zero_if_nan(margin_bottom);

                    draw_list->AddRectFilled(pos_left__top_left, pos_left__bot_right, style->position_offset_color);

                    // Draw text
                    {
                        const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, pos_offset_left);
                        const ImVec2 txt_pos = utils::rect_center(pos_left__top_left, pos_left__bot_right);

                        utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                    }
                }

                if( !YGFloatIsUndefined(pos_offset_top) && (pos_offset_top != 0.0f) )
                {
                    ImVec2 pos_top__top_left  = {node_rect__top_left.x, node_rect__top_left.y - pos_offset_top};
                    ImVec2 pos_top__bot_right = {node_rect__bot_right.x, node_rect__top_left.y};

                    // Shift by margin
                    pos_top__top_left.y  -= utils::zero_if_nan(margin_top);
                    pos_top__bot_right.y -= utils::zero_if_nan(margin_top);

                    // Enlarve horizontally to fill empty space, if margin is set. Also add horizontal 'position offsets' to fill empty areas
                    pos_top__top_left.x  -= utils::zero_if_nan(margin_left)  + utils::zero_if_nan(pos_offset_left);
                    pos_top__bot_right.x += utils::zero_if_nan(margin_right) + utils::zero_if_nan(pos_offset_right);

                    draw_list->AddRectFilled(pos_top__top_left, pos_top__bot_right, style->position_offset_color);

                    // Draw text
                    {
                        const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, pos_offset_top);
                        const ImVec2 txt_pos = utils::rect_center(pos_top__top_left, pos_top__bot_right);

                        utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                    }
                }

                if( !YGFloatIsUndefined(pos_offset_right) && (pos_offset_right != 0.0f) )
                {
                    ImVec2 pos_right__top_left  = {node_rect__bot_right.x, node_rect__top_left.y};
                    ImVec2 pos_right__bot_right = {node_rect__bot_right.x + pos_offset_right, node_rect__bot_right.y};

                    // Shift by margin
                    pos_right__top_left.x  += utils::zero_if_nan(margin_right);
                    pos_right__bot_right.x += utils::zero_if_nan(margin_right);

                    // Enlarve vertically to fill empty space, if margin is set
                    pos_right__top_left.y  -= utils::zero_if_nan(margin_top);
                    pos_right__bot_right.y += utils::zero_if_nan(margin_bottom);

                    draw_list->AddRectFilled(pos_right__top_left, pos_right__bot_right, style->position_offset_color);

                    // Draw text
                    {
                        const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, pos_offset_right);
                        const ImVec2 txt_pos = utils::rect_center(pos_right__top_left, pos_right__bot_right);

                        utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                    }
                }

                if( !YGFloatIsUndefined(pos_offset_bottom) && (pos_offset_bottom != 0.0f) )
                {
                    ImVec2 pos_bottom__top_left  = {node_rect__top_left.x, node_rect__bot_right.y};
                    ImVec2 pos_bottom__bot_right = {node_rect__bot_right.x, node_rect__bot_right.y + pos_offset_bottom};

                    // Shift by margin
                    pos_bottom__top_left.y  += utils::zero_if_nan(margin_bottom);
                    pos_bottom__bot_right.y += utils::zero_if_nan(margin_bottom);

                    // Enlarve horizontally to fill empty space, if margin is set. Also add horizontal 'position offsets' to fill empty areas
                    pos_bottom__top_left.x  -= utils::zero_if_nan(margin_left)  + utils::zero_if_nan(pos_offset_left);
                    pos_bottom__bot_right.x += utils::zero_if_nan(margin_right) + utils::zero_if_nan(pos_offset_right);

                    draw_list->AddRectFilled(pos_bottom__top_left, pos_bottom__bot_right, style->position_offset_color);

                    // Draw text
                    {
                        const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, pos_offset_bottom);
                        const ImVec2 txt_pos = utils::rect_center(pos_bottom__top_left, pos_bottom__bot_right);

                        utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                    }
                }
            }
        }

        // Draw margins
        {
            /*
                Note: Negative margins displayed not the same as on website (yogalayout.com).
                Well ... on website them displayed without overlapping, but display
                margins, which NOT the same, as we get from 'layout'
             */

            if( !YGFloatIsUndefined(margin_left) && (margin_left != 0.0f) )
            {
                ImVec2 margin_left__top_left  = {node_rect__top_left.x - margin_left, node_rect__top_left.y};
                ImVec2 margin_left__bot_right = {node_rect__top_left.x, node_rect__bot_right.y};

                draw_list->AddRectFilled(margin_left__top_left, margin_left__bot_right, style->margin_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, margin_left);
                    const ImVec2 txt_pos = utils::rect_center(margin_left__top_left, margin_left__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(margin_top) && (margin_top != 0.0f) )
            {
                ImVec2 margin_top__top_left  = {node_rect__top_left.x, node_rect__top_left.y - margin_top};
                ImVec2 margin_top__bot_right = {node_rect__bot_right.x, node_rect__top_left.y};

                // Expand horizontally to fill 'empty' areas
                margin_top__top_left.x  -= utils::zero_if_nan(margin_left);
                margin_top__bot_right.x += utils::zero_if_nan(margin_right);

                draw_list->AddRectFilled(margin_top__top_left, margin_top__bot_right, style->margin_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, margin_top);
                    const ImVec2 txt_pos = utils::rect_center(margin_top__top_left, margin_top__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(margin_right) && (margin_right != 0.0f) )
            {
                ImVec2 margin_right__top_left  = {node_rect__bot_right.x, node_rect__top_left.y};
                ImVec2 margin_right__bot_right = {node_rect__bot_right.x + margin_right, node_rect__bot_right.y};

                draw_list->AddRectFilled(margin_right__top_left, margin_right__bot_right, style->margin_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, margin_right);
                    const ImVec2 txt_pos = utils::rect_center(margin_right__top_left, margin_right__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(margin_bottom) && (margin_bottom != 0.0f) )
            {
                ImVec2 margin_bottom__top_left  = {node_rect__top_left.x, node_rect__bot_right.y};
                ImVec2 margin_bottom__bot_right = {node_rect__bot_right.x, node_rect__bot_right.y + margin_bottom};

                // Expand horizontally to fill 'empty' areas
                margin_bottom__top_left.x  -= utils::zero_if_nan(margin_left);
                margin_bottom__bot_right.x += utils::zero_if_nan(margin_right);

                draw_list->AddRectFilled(margin_bottom__top_left, margin_bottom__bot_right, style->margin_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, margin_bottom);
                    const ImVec2 txt_pos = utils::rect_center(margin_bottom__top_left, margin_bottom__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }
        }

        // Draw borders
        {
            if( !YGFloatIsUndefined(border_left) && (border_left != 0.0f) )
            {
                ImVec2 border_left__top_left  = node_rect__top_left;
                ImVec2 border_left__bot_right = { node_rect__top_left.x + border_left, node_rect__bot_right.y };

                // Dont resize vertically, to not produce 'empty' areas
                //border_left__top_left.y  += utils::zero_if_nan(border_top);
                //border_left__bot_right.y -= utils::zero_if_nan(border_bottom);

                draw_list->AddRectFilled(border_left__top_left, border_left__bot_right, style->border_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, border_left);
                    const ImVec2 txt_pos = utils::rect_center(border_left__top_left, border_left__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(border_top) && (border_top != 0.0f) )
            {
                ImVec2 border_top__top_left  = node_rect__top_left;
                ImVec2 border_top__bot_right = {node_rect__bot_right.x, node_rect__top_left.y + border_top};

                // Resize horizontally, to not overlap
                border_top__top_left.x  += utils::zero_if_nan(border_left);
                border_top__bot_right.x -= utils::zero_if_nan(border_right);

                draw_list->AddRectFilled(border_top__top_left, border_top__bot_right, style->border_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, border_top);
                    const ImVec2 txt_pos = utils::rect_center(border_top__top_left, border_top__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(border_right) && (border_right != 0.0f) )
            {
                ImVec2 border_right__top_left  = {node_rect__bot_right.x - border_right, node_rect__top_left.y};
                ImVec2 border_right__bot_right = node_rect__bot_right;

                // Dont resize vertically, to not produce 'empty' areas
                //border_right__top_left.y  += utils::zero_if_nan(border_top);
                //border_right__bot_right.y -= utils::zero_if_nan(border_bottom);

                draw_list->AddRectFilled(border_right__top_left, border_right__bot_right, style->border_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, border_right);
                    const ImVec2 txt_pos = utils::rect_center(border_right__top_left, border_right__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(border_bottom) && (border_bottom != 0.0f) )
            {
                ImVec2 border_bottom__top_left  = {node_rect__top_left.x, node_rect__bot_right.y - border_bottom};
                ImVec2 border_bottom__bot_right = node_rect__bot_right;

                // Resize horizontally, to not overlap
                border_bottom__top_left.x  += utils::zero_if_nan(border_left);
                border_bottom__bot_right.x -= utils::zero_if_nan(border_right);

                draw_list->AddRectFilled(border_bottom__top_left, border_bottom__bot_right, style->border_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, border_bottom);
                    const ImVec2 txt_pos = utils::rect_center(border_bottom__top_left, border_bottom__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }
        }

        // Draw paddings
        {
            if( !YGFloatIsUndefined(padding_left) && (padding_left != 0.0f) )
            {
                ImVec2 padding_left__top_left  = node_rect__top_left;
                ImVec2 padding_left__bot_right = { node_rect__top_left.x + padding_left, node_rect__bot_right.y };

                // Border offseting
                padding_left__top_left.x  += utils::zero_if_nan(border_left);
                padding_left__bot_right.x += utils::zero_if_nan(border_left);

                // Dont resize vertically, to not produce 'empty' areas (exclude padding)
                padding_left__top_left.y  += utils::zero_if_nan(border_top)    /* + utils::zero_if_nan(padding_top) */;
                padding_left__bot_right.y -= utils::zero_if_nan(border_bottom) /* + utils::zero_if_nan(padding_bottom) */;

                draw_list->AddRectFilled(padding_left__top_left, padding_left__bot_right, style->padding_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, padding_left);
                    const ImVec2 txt_pos = utils::rect_center(padding_left__top_left, padding_left__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(padding_top) && (padding_top != 0.0f) )
            {
                ImVec2 padding_top__top_left  = node_rect__top_left;
                ImVec2 padding_top__bot_right = { node_rect__bot_right.x, node_rect__top_left.y + padding_top };

                // Border offsetings
                padding_top__top_left.y  += utils::zero_if_nan(border_top);
                padding_top__bot_right.y += utils::zero_if_nan(border_top);

                // Resize horizontally, to not overlap
                padding_top__top_left.x  += utils::zero_if_nan(border_left)  + utils::zero_if_nan(padding_left);
                padding_top__bot_right.x -= utils::zero_if_nan(border_right) + utils::zero_if_nan(padding_right);

                draw_list->AddRectFilled(padding_top__top_left, padding_top__bot_right, style->padding_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, padding_top);
                    const ImVec2 txt_pos = utils::rect_center(padding_top__top_left, padding_top__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(padding_right) && (padding_right != 0.0f) )
            {
                ImVec2 padding_right__top_left  = { node_rect__bot_right.x - padding_right, node_rect__top_left.y };
                ImVec2 padding_right__bot_right = node_rect__bot_right;

                // Border offseting
                padding_right__top_left.x  -= utils::zero_if_nan(border_right);
                padding_right__bot_right.x -= utils::zero_if_nan(border_right);

                // Dont resize vertically, to not produce 'empty' areas (exclude padding)
                padding_right__top_left.y  += utils::zero_if_nan(border_top)    /* + utils::zero_if_nan(padding_top) */;
                padding_right__bot_right.y -= utils::zero_if_nan(border_bottom) /* + utils::zero_if_nan(padding_bottom) */;

                draw_list->AddRectFilled(padding_right__top_left, padding_right__bot_right, style->padding_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, padding_right);
                    const ImVec2 txt_pos = utils::rect_center(padding_right__top_left, padding_right__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }

            if( !YGFloatIsUndefined(padding_bottom) && (padding_bottom != 0.0f) )
            {
                ImVec2 padding_bottom__top_left = { node_rect__top_left.x, node_rect__bot_right.y - padding_bottom };
                ImVec2 padding_bottom__bot_right = node_rect__bot_right;

                // Border offseting
                padding_bottom__top_left.y  -= utils::zero_if_nan(border_bottom);
                padding_bottom__bot_right.y -= utils::zero_if_nan(border_bottom);

                // Resize horizontally, to not overlap
                padding_bottom__top_left.x  += utils::zero_if_nan(border_left)  + utils::zero_if_nan(padding_left);
                padding_bottom__bot_right.x -= utils::zero_if_nan(border_right) + utils::zero_if_nan(padding_right);

                draw_list->AddRectFilled(padding_bottom__top_left, padding_bottom__bot_right, style->padding_color);

                // Draw text
                {
                    const int text_length = utils::print_float_without_trailing_zeros(text_buffer, TEXT_BUFFER_SIZE, padding_bottom);
                    const ImVec2 txt_pos = utils::rect_center(padding_bottom__top_left, padding_bottom__bot_right);

                    utils::draw_text_centered(draw_list, txt_pos, style->values_color, text_buffer, text_buffer + text_length);
                }
            }
        }
    }

    // Draw childs recursively
    const uint32_t childs_count = YGNodeGetChildCount(node);
    for(uint32_t child_idx = 0; child_idx < childs_count; child_idx++)
    {
        YGNodeRef child = YGNodeGetChild(node, child_idx);

        YGNode_draw_recursive(
                    child,
                    draw_list,

                    node_rect__top_left, // origin is 'parent TopLeft corner'
                    focused_node,

                    style
        );
    }
}
