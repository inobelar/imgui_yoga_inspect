#ifndef IMGUI_YOGA__YGNODE_DRAW_RECURSIVE_HPP
#define IMGUI_YOGA__YGNODE_DRAW_RECURSIVE_HPP

#include <yoga/Yoga.h>
#include <imgui.h>

namespace ImGui_Yoga {

struct YGNode_Draw_Style
{
    ImU32 node_nonfocused_color;
    ImU32 node_focused_color;

    float node_nonfocused_thickness;
    float node_focused_thickness;

    ImU32 position_offset_color;
    ImU32 margin_color;
    ImU32 border_color;
    ImU32 padding_color;

    ImU32 values_color;

    YGNode_Draw_Style();
};


// NOTE: 'YGNodeRef node', instead of 'YGNodeConstRef node', since some
// Yoga functions for getting data accept only this type.
void YGNode_draw_recursive(
        YGNodeRef node,
        ImDrawList* draw_list,

        const ImVec2& origin,
        YGNodeConstRef focused_node = nullptr,

        const YGNode_Draw_Style* style = nullptr
);

} // namespace ImGui_Yoga

#endif // IMGUI_YOGA__YGNODE_DRAW_RECURSIVE_HPP
