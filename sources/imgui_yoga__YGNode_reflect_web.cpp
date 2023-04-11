#include <ImGui_Yoga/YGNode_reflect_web.hpp>

#include <imgui.h>

#include <ImGui_Yoga/enums.hpp>
#include <ImGui_Yoga/YGValue_widgets.hpp>

#include <ImGui_Yoga/utility_widgets.hpp>

bool ImGui_Yoga::YGNode_reflect_web(YGNodeRef node)
{
    if(node == nullptr)
    {
        return false;
    }

    bool modified = false;

    const ImVec2 SEPARATOR_RECT = {0.0f, ImGui::GetFontSize() / 2.0f };

    const bool is_root = (YGNodeGetParent(node) == nullptr);

    constexpr ImGuiTabBarFlags TAB_BAR_FLAGS = ImGuiTabBarFlags_None;
    if( ImGui::BeginTabBar("categories", TAB_BAR_FLAGS) )
    {
        if( ImGui::BeginTabItem("Flex") )
        {
            // Direction
            {
                ImGui::TextUnformatted("DIRECTION");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Defines the direction of which text and items are laid out");

                YGDirection direction = YGNodeStyleGetDirection(node);

                if ( ImGui_Yoga::YGDirection_radio(direction) )
                {
                    YGNodeStyleSetDirection(node, direction);
                    modified = true;
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Flex Direction
            {
                ImGui::TextUnformatted("FLEX DIRECTION");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Defines the direction of the main-axis");

                YGFlexDirection flex_direction = YGNodeStyleGetFlexDirection(node);

                ImGui::SetNextItemWidth(-FLT_MIN); // Stretch full width
                if( ImGui_Yoga::YGFlexDirection_combo("##flex_direction", flex_direction) )
                {
                    YGNodeStyleSetFlexDirection(node, flex_direction);
                    modified = true;
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Basis & Grow & Shrink
            {
                // Basis
                ImGui::BeginGroup();
                {
                    ImGui::TextUnformatted("BASIS");
                    ImGui::SameLine();
                    ImGui_Yoga::HelpMarker("Default size of a node along the main axis");

                    YGValue flex_basis = YGNodeStyleGetFlexBasis(node);

                    if(is_root)
                    {
                        ImGui_Yoga::YGValue_text_disabled(flex_basis);
                    }
                    else
                    {
                        if( ImGui_Yoga::YGValue_edit("##flex_basis", flex_basis) ) // TODO: 'point', 'percent' or 'auto' only!
                        {
                            switch(flex_basis.unit) {
                            case YGUnit::YGUnitPoint:   { YGNodeStyleSetFlexBasis(node, flex_basis.value); } break;
                            case YGUnit::YGUnitPercent: { YGNodeStyleSetFlexBasisPercent(node, flex_basis.value); } break;
                            case YGUnit::YGUnitAuto:    { YGNodeStyleSetFlexBasisAuto(node); } break;

                            case YGUnit::YGUnitUndefined: { YGNodeStyleSetFlexBasis(node, YGUndefined); } break;
                            }

                            modified = true;
                        }
                    }
                }
                ImGui::EndGroup();

                ImGui::SameLine();

                // Grow
                ImGui::BeginGroup();
                {
                    ImGui::TextUnformatted("GROW");
                    ImGui::SameLine();
                    ImGui_Yoga::HelpMarker("The factor of remaining space should be given to this node");

                    float flex_grow = YGNodeStyleGetFlexGrow(node);

                    if(is_root)
                    {
                        ImGui::TextDisabled("%f", flex_grow);
                    }
                    else
                    {
                        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 5);
                        if( ImGui::DragFloat("##flex_grow", &flex_grow) )
                        {
                            YGNodeStyleSetFlexGrow(node, flex_grow);

                            modified = true;
                        }
                    }
                }
                ImGui::EndGroup();

                ImGui::SameLine();

                // Shrink
                ImGui::BeginGroup();
                {
                    ImGui::TextUnformatted("SHRINK");
                    ImGui::SameLine();
                    ImGui_Yoga::HelpMarker("The shrink factor of this element if parent has no space left");

                    float flex_shrink = YGNodeStyleGetFlexShrink(node);

                    if(is_root)
                    {
                        ImGui::TextDisabled("%f", flex_shrink);
                    }
                    else
                    {
                        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 5);
                        if( ImGui::DragFloat("##flex_shrink", &flex_shrink) )
                        {
                            YGNodeStyleSetFlexShrink(node, flex_shrink);

                            modified = true;
                        }
                    }
                }
                ImGui::EndGroup();
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Flex wrap
            {
                ImGui::TextUnformatted("FLEX WRAP");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Wrapping behaviour when child nodes don't fit into a single line");

                YGWrap flex_wrap = YGNodeStyleGetFlexWrap(node);

                if( ImGui_Yoga::YGWrap_radio(flex_wrap) )
                {
                    YGNodeStyleSetFlexWrap(node, flex_wrap);

                    modified = true;
                }
            }

            ImGui::EndTabItem();
        }

        if( ImGui::BeginTabItem("Alignment") )
        {
            // Justify content
            {
                ImGui::TextUnformatted("JUSTIFY CONTENT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Aligns child nodes along the main-axis");

                YGJustify justify_content = YGNodeStyleGetJustifyContent(node);

                ImGui::SetNextItemWidth(-FLT_MIN); // Stretch full width
                if( ImGui_Yoga::YGJustify_combo("##justify_content", justify_content) )
                {
                    YGNodeStyleSetJustifyContent(node, justify_content);

                    modified = true;
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Align items
            {
                ImGui::TextUnformatted("ALIGN ITEMS");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Aligns child nodes along the cross-axis");

                YGAlign align_items = YGNodeStyleGetAlignItems(node);

                 ImGui::SetNextItemWidth(-FLT_MIN); // Stretch full width
                if( ImGui_Yoga::YGAlign_combo("##align_items", align_items) )
                {
                    YGNodeStyleSetAlignItems(node, align_items);

                    modified = true;
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Align self
            {
                ImGui::TextUnformatted("ALIGN SELF");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Override align items of parent");

                YGAlign align_self = YGNodeStyleGetAlignSelf(node);

                if(is_root)
                {
                    ImGui::TextDisabled("%s", YGAlignToString(align_self) );
                }
                else
                {
                    ImGui::SetNextItemWidth(-FLT_MIN); // Stretch full width
                    if( ImGui_Yoga::YGAlign_combo("##align_self", align_self) )
                    {
                        YGNodeStyleSetAlignSelf(node, align_self);

                        modified = true;
                    }
                }

            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Align content
            {
                ImGui::TextUnformatted("ALIGN CONTENT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Alignment of lines along the cross-axis when wrapping");

                YGAlign align_content = YGNodeStyleGetAlignContent(node);

                ImGui::SetNextItemWidth(-FLT_MIN); // Stretch full width
                if( ImGui_Yoga::YGAlign_combo("##align_content", align_content) )
                {
                    YGNodeStyleSetAlignContent(node, align_content);

                    modified = true;
                }
            }

            ImGui::EndTabItem();
        }

        if( ImGui::BeginTabItem("Layout") )
        {
            // Width x Height
            {
                ImGui::TextUnformatted("WIDTH x HEIGHT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Dimensions of the node");

                {
                    YGValue width  = YGNodeStyleGetWidth(node);

                    if( ImGui_Yoga::YGValue_edit("##width", width) )
                    {
                        switch(width.unit) {
                        case YGUnit::YGUnitPoint:   { YGNodeStyleSetWidth(node, width.value); } break;
                        case YGUnit::YGUnitPercent: { YGNodeStyleSetWidthPercent(node, width.value); } break;
                        case YGUnit::YGUnitAuto:    { YGNodeStyleSetWidthAuto(node); } break;

                        case YGUnit::YGUnitUndefined: { YGNodeStyleSetWidth(node, YGUndefined); } break;
                        }

                        modified = true;
                    }
                }

                ImGui::SameLine();

                {
                    YGValue height = YGNodeStyleGetHeight(node);

                    if( ImGui_Yoga::YGValue_edit("##height", height) )
                    {
                        switch(height.unit) {
                        case YGUnit::YGUnitPoint:   { YGNodeStyleSetHeight(node, height.value); } break;
                        case YGUnit::YGUnitPercent: { YGNodeStyleSetHeightPercent(node, height.value); } break;
                        case YGUnit::YGUnitAuto:    { YGNodeStyleSetHeightAuto(node); } break;

                        case YGUnit::YGUnitUndefined: { YGNodeStyleSetHeight(node, YGUndefined); } break;
                        }

                        modified = true;
                    }
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Max-width x Max-height
            {
                ImGui::TextUnformatted("MAX-WIDTH x MAX-HEIGHT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Maximum dimensions of the node");

                {
                    YGValue max_width  = YGNodeStyleGetMaxWidth(node);

                    if( ImGui_Yoga::YGValue_edit("##max_width", max_width) )
                    {
                        switch(max_width.unit) {
                        case YGUnit::YGUnitPoint:   { YGNodeStyleSetMaxWidth(node, max_width.value); } break;
                        case YGUnit::YGUnitPercent: { YGNodeStyleSetMaxWidthPercent(node, max_width.value); } break;

                        case YGUnit::YGUnitUndefined: { YGNodeStyleSetMaxWidth(node, YGUndefined); } break;
                        case YGUnit::YGUnitAuto:      { YGNodeStyleSetMaxWidth(node, YGUndefined); } break;
                        }

                        modified = true;
                    }
                }

                ImGui::SameLine();

                {
                    YGValue max_height = YGNodeStyleGetMaxHeight(node);

                    if( ImGui_Yoga::YGValue_edit("##max_height", max_height) )
                    {
                        switch(max_height.unit) {
                        case YGUnit::YGUnitPoint:   { YGNodeStyleSetMaxHeight(node, max_height.value); } break;
                        case YGUnit::YGUnitPercent: { YGNodeStyleSetMaxHeightPercent(node, max_height.value); } break;

                        case YGUnit::YGUnitUndefined: { YGNodeStyleSetMaxHeight(node, YGUndefined); } break;
                        case YGUnit::YGUnitAuto:      { YGNodeStyleSetMaxHeight(node, YGUndefined); } break;
                        }

                        modified = true;
                    }
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Min-width x Min-height
            {
                ImGui::TextUnformatted("MIN-WIDTH x MIN-HEIGHT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Minimum dimensions of the node");

                {
                    YGValue min_width  = YGNodeStyleGetMinWidth(node);

                    if( ImGui_Yoga::YGValue_edit("##min_width", min_width) )
                    {
                        switch(min_width.unit) {
                        case YGUnit::YGUnitPoint:   { YGNodeStyleSetMinWidth(node, min_width.value); } break;
                        case YGUnit::YGUnitPercent: { YGNodeStyleSetMinWidthPercent(node, min_width.value); } break;

                        case YGUnit::YGUnitUndefined: { YGNodeStyleSetMinWidth(node, YGUndefined); } break;
                        case YGUnit::YGUnitAuto:      { YGNodeStyleSetMinWidth(node, YGUndefined); } break;
                        }

                        modified = true;
                    }
                }

                ImGui::SameLine();

                {
                    YGValue min_height = YGNodeStyleGetMinHeight(node);

                    if( ImGui_Yoga::YGValue_edit("##min_height", min_height) )
                    {
                        switch(min_height.unit) {
                        case YGUnit::YGUnitPoint:   { YGNodeStyleSetMinHeight(node, min_height.value); } break;
                        case YGUnit::YGUnitPercent: { YGNodeStyleSetMinHeightPercent(node, min_height.value); } break;

                        case YGUnit::YGUnitUndefined: { YGNodeStyleSetMinHeight(node, YGUndefined); } break;
                        case YGUnit::YGUnitAuto:      { YGNodeStyleSetMinHeight(node, YGUndefined); } break;
                        }

                        modified = true;
                    }
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Aspect ratio (TODO: somehow allow to set 'auto' float ... possibly it is nan)
            {
                ImGui::TextUnformatted("ASPECT RATIO");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Width/Height aspect ratio of node");

                float aspect_ratio = YGNodeStyleGetAspectRatio(node);

                ImGui::SetNextItemWidth(-FLT_MIN); // Stretch full width
                if( ImGui::DragFloat("##aspect_ratio", &aspect_ratio))
                {
                    YGNodeStyleSetAspectRatio(node, aspect_ratio);

                    modified = true;
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Padding
            {
                if( ImGui::BeginTable("padding_table", 3) )
                {
                    // Top row -----------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeTop;

                            YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            if( ImGui_Yoga::YGValue_edit("##padding_top", padding) )
                            {
                                switch(padding.unit) {
                                case YGUnit::YGUnitPoint:   { YGNodeStyleSetPadding(node, PADDIGN_SIDE, padding.value); } break;
                                case YGUnit::YGUnitPercent: { YGNodeStyleSetPaddingPercent(node, PADDIGN_SIDE, padding.value); } break;

                                case YGUnit::YGUnitUndefined: { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                case YGUnit::YGUnitAuto:      { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                }

                                modified = true;
                            }
                        }
                    }

                    // Middle row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(0);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeLeft;

                            YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            if( ImGui_Yoga::YGValue_edit("##padding_left", padding) )
                            {
                                switch(padding.unit) {
                                case YGUnit::YGUnitPoint:   { YGNodeStyleSetPadding(node, PADDIGN_SIDE, padding.value); } break;
                                case YGUnit::YGUnitPercent: { YGNodeStyleSetPaddingPercent(node, PADDIGN_SIDE, padding.value); } break;

                                case YGUnit::YGUnitUndefined: { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                case YGUnit::YGUnitAuto:      { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                }

                                modified = true;
                            }
                        }

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("PADDING");

                        ImGui::TableSetColumnIndex(2);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeRight;

                            YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            if( ImGui_Yoga::YGValue_edit("##padding_right", padding) )
                            {
                                switch(padding.unit) {
                                case YGUnit::YGUnitPoint:   { YGNodeStyleSetPadding(node, PADDIGN_SIDE, padding.value); } break;
                                case YGUnit::YGUnitPercent: { YGNodeStyleSetPaddingPercent(node, PADDIGN_SIDE, padding.value); } break;

                                case YGUnit::YGUnitUndefined: { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                case YGUnit::YGUnitAuto:      { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                }

                                modified = true;
                            }
                        }
                    }

                    // Bottom row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeBottom;

                            YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            if( ImGui_Yoga::YGValue_edit("##padding_bottom", padding) )
                            {
                                switch(padding.unit) {
                                case YGUnit::YGUnitPoint:   { YGNodeStyleSetPadding(node, PADDIGN_SIDE, padding.value); } break;
                                case YGUnit::YGUnitPercent: { YGNodeStyleSetPaddingPercent(node, PADDIGN_SIDE, padding.value); } break;

                                case YGUnit::YGUnitUndefined: { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                case YGUnit::YGUnitAuto:      { YGNodeStyleSetPadding(node, PADDIGN_SIDE, YGUndefined); } break;
                                }

                                modified = true;
                            }
                        }
                    }

                    ImGui::EndTable();
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Border
            {
                if( ImGui::BeginTable("border_table", 3) )
                {
                    // Top row -----------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeTop;

                            float border = YGNodeStyleGetBorder(node, BORDER_SIDE);
                            if( ImGui::DragFloat("##border_top", &border) )
                            {
                                YGNodeStyleSetBorder(node, BORDER_SIDE, border);

                                modified = true;
                            }
                        }
                    }

                    // Middle row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(0);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeLeft;

                            float border = YGNodeStyleGetBorder(node, BORDER_SIDE);
                            if( ImGui::DragFloat("##border_left", &border) )
                            {
                                YGNodeStyleSetBorder(node, BORDER_SIDE, border);

                                modified = true;
                            }
                        }

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("BORDER");

                        ImGui::TableSetColumnIndex(2);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeRight;

                            float border = YGNodeStyleGetBorder(node, BORDER_SIDE);
                            if( ImGui::DragFloat("##border_right", &border) )
                            {
                                YGNodeStyleSetBorder(node, BORDER_SIDE, border);

                                modified = true;
                            }
                        }
                    }

                    // Bottom row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeBottom;

                            float border = YGNodeStyleGetBorder(node, BORDER_SIDE);
                            if( ImGui::DragFloat("##border_bottom", &border) )
                            {
                                YGNodeStyleSetBorder(node, BORDER_SIDE, border);

                                modified = true;
                            }
                        }
                    }

                    ImGui::EndTable();
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Margin
            {
                if( ImGui::BeginTable("margin_table", 3) )
                {
                    // Top row -----------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeTop;

                            YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                if( ImGui_Yoga::YGValue_edit("##margin_top", margin) )
                                {
                                    switch(margin.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMargin(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMarginPercent(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMarginAuto(node, MARGIN_SIDE); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMargin(node, MARGIN_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }
                    }

                    // Middle row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(0);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeLeft;

                            YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                if( ImGui_Yoga::YGValue_edit("##margin_left", margin) )
                                {
                                    switch(margin.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMargin(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMarginPercent(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMarginAuto(node, MARGIN_SIDE); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMargin(node, MARGIN_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("MARGIN");

                        ImGui::TableSetColumnIndex(2);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeRight;

                            YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                if( ImGui_Yoga::YGValue_edit("##margin_right", margin) )
                                {
                                    switch(margin.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMargin(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMarginPercent(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMarginAuto(node, MARGIN_SIDE); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMargin(node, MARGIN_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }
                    }

                    // Bottom row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeBottom;

                            YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                if( ImGui_Yoga::YGValue_edit("##margin_bottom", margin) )
                                {
                                    switch(margin.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMargin(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMarginPercent(node, MARGIN_SIDE, margin.value); } break;
                                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMarginAuto(node, MARGIN_SIDE); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMargin(node, MARGIN_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }
                    }

                    ImGui::EndTable();
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Position Type & Position
            {
                ImGui::TextUnformatted("POSITION TYPE");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Relative position offsets the node\nfrom it's calculated position.\nAbsolute position removes the node\nfrom the flexbox flow and positions it\nat the given position.");

                // Position type
                {
                    YGPositionType pos_type = YGNodeStyleGetPositionType(node);

                    if(is_root)
                    {
                        ImGui::TextDisabled("%s", YGPositionTypeToString(pos_type) );
                    }
                    else
                    {
                        if( ImGui_Yoga::YGPositionType_radio(pos_type) )
                        {
                            YGNodeStyleSetPositionType(node, pos_type);

                            modified = true;
                        }
                    }
                }

                ImGui::Dummy(SEPARATOR_RECT); // Separator

                // Position
                {
                    if( ImGui::BeginTable("position_table", 3) )
                    {
                        // Top row -----------------------------------------
                        ImGui::TableNextRow();
                        {
                            ImGui::TableSetColumnIndex(1);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeTop;

                                YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                if( ImGui_Yoga::YGValue_edit("##position_top", position) )
                                {
                                    switch(position.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetPosition(node, POS_SIDE, position.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetPositionPercent(node, POS_SIDE, position.value); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    case YGUnit::YGUnitAuto:      { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }

                        // Middle row --------------------------------------
                        ImGui::TableNextRow();
                        {
                            ImGui::TableSetColumnIndex(0);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeLeft;

                                YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                if( ImGui_Yoga::YGValue_edit("##position_left", position) )
                                {
                                    switch(position.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetPosition(node, POS_SIDE, position.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetPositionPercent(node, POS_SIDE, position.value); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    case YGUnit::YGUnitAuto:      { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }

                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text("POSITION");

                            ImGui::TableSetColumnIndex(2);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeRight;

                                YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                if( ImGui_Yoga::YGValue_edit("##position_right", position) )
                                {
                                    switch(position.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetPosition(node, POS_SIDE, position.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetPositionPercent(node, POS_SIDE, position.value); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    case YGUnit::YGUnitAuto:      { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }

                        // Bottom row --------------------------------------
                        ImGui::TableNextRow();
                        {
                            ImGui::TableSetColumnIndex(1);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeBottom;

                                YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                if( ImGui_Yoga::YGValue_edit("##position_bottom", position) )
                                {
                                    switch(position.unit) {
                                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetPosition(node, POS_SIDE, position.value); } break;
                                    case YGUnit::YGUnitPercent: { YGNodeStyleSetPositionPercent(node, POS_SIDE, position.value); } break;

                                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    case YGUnit::YGUnitAuto:      { YGNodeStyleSetPosition(node, POS_SIDE, YGUndefined); } break;
                                    }

                                    modified = true;
                                }
                            }
                        }

                        ImGui::EndTable();
                    }
                }
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    return modified;
}
