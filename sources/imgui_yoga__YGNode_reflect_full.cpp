#include <ImGui_Yoga/YGNode_reflect_full.hpp>

#include <imgui.h>

#include <ImGui_Yoga/enums.hpp>
#include <ImGui_Yoga/YGValue_widgets.hpp>

#include <string>

bool ImGui_Yoga::YGNode_reflect_full(YGNodeRef node)
{
    if(node == nullptr)
    {
        return false;
    }

    bool modified = false;

    constexpr ImGuiTableFlags TABLE_FLAGS =
        ImGuiTableFlags_Resizable      |
        ImGuiTableFlags_BordersInnerV  |
      //ImGuiTableFlags_SizingFixedFit |
        ImGuiTableFlags_NoSavedSettings;
    constexpr char TABLE_ID[] = "node_data_table";

    ImGui::SeparatorText("Node");
    {
        // Parent
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGNodeRef parent = YGNodeGetParent(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Parent");

            ImGui::TableNextColumn();
            ImGui::Text("%p", parent);

            ImGui::EndTable();
        }

        // Childs
        {
            const uint32_t child_count = YGNodeGetChildCount(node);

            if(child_count > 0)
            {
                if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
                {
                    for(uint32_t child_idx = 0; child_idx < child_count; ++child_idx)
                    {
                        const YGNodeRef child = YGNodeGetChild(node, child_idx);

                        ImGui::TableNextColumn();
                        ImGui::Text("Child %d", child_idx);

                        ImGui::TableNextColumn();
                        ImGui::Text("%p", child);
                    }

                    ImGui::EndTable();
                }
            }
        }

        // IsReferenceBaseline
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            bool is_reference_baseline = YGNodeIsReferenceBaseline(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Is Reference Baseline");

            ImGui::TableNextColumn();
            if( ImGui::Checkbox("##is_reference_baseline", &is_reference_baseline) )
            {
                YGNodeSetIsReferenceBaseline(node, is_reference_baseline);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Dirty
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            bool is_dirty = YGNodeIsDirty(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Is dirty");

            ImGui::TableNextColumn();
            if( ImGui::Checkbox("##is_dirty", &is_dirty) )
            {
                if(is_dirty == true) // TODO: add check for hasMeasuseFunc, otherwise it assert()
                {
                    YGNodeMarkDirty(node);
                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Context
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const void* context = YGNodeGetContext(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Context");

            ImGui::TableNextColumn();
            ImGui::Text("%p", context);

            ImGui::EndTable();
        }

        // Funcs
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Measure
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Has measure func");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted(YGNodeHasMeasureFunc(node) ? "true" : "false");
            }

            // Baseline
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Has baseline func");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted(YGNodeHasBaselineFunc(node) ? "true" : "false");
            }

            // Dirtied
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Has dirtied func");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted((YGNodeGetDirtiedFunc(node) != nullptr) ? "true" : "false");
            }

            ImGui::EndTable();
        }

        // New layout
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            bool has_new_layout = YGNodeGetHasNewLayout(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Has new layout");

            ImGui::TableNextColumn();
            if( ImGui::Checkbox("##has_new_layout", &has_new_layout) )
            {
                YGNodeSetHasNewLayout(node, has_new_layout);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Node type
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGNodeType node_type = YGNodeGetNodeType(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Node type");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGNodeType_combo("##node_type", node_type) )
            {
                YGNodeSetNodeType(node, node_type);
                modified = true;
            }

            ImGui::EndTable();
        }
    }

    ImGui::SeparatorText("Style");
    {
        // Direction
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGDirection direction = YGNodeStyleGetDirection(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Direction");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGDirection_combo("##direction", direction) )
            {
                YGNodeStyleSetDirection(node, direction);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Flex Direction
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGFlexDirection flex_direction = YGNodeStyleGetFlexDirection(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex direction");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGFlexDirection_combo("##flex_direction", flex_direction) )
            {
                YGNodeStyleSetFlexDirection(node, flex_direction);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Justify content
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGJustify justify_content = YGNodeStyleGetJustifyContent(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Justify content");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGJustify_combo("##justify_content", justify_content) )
            {
                YGNodeStyleSetJustifyContent(node, justify_content);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Align
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Content
            {
                YGAlign align_content = YGNodeStyleGetAlignContent(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align content");

                ImGui::TableNextColumn();
                if( ImGui_Yoga::YGAlign_combo("##align_content", align_content) )
                {
                    YGNodeStyleSetAlignContent(node, align_content);
                    modified = true;
                }
            }

            // Items
            {
                YGAlign align_items = YGNodeStyleGetAlignItems(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align items");

                ImGui::TableNextColumn();
                if( ImGui_Yoga::YGAlign_combo("##align_items", align_items) )
                {
                    YGNodeStyleSetAlignItems(node, align_items);
                    modified = true;
                }
            }

            // Self
            {
                YGAlign align_self = YGNodeStyleGetAlignSelf(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align self");

                ImGui::TableNextColumn();
                if( ImGui_Yoga::YGAlign_combo("##align_self", align_self) )
                {
                    YGNodeStyleSetAlignSelf(node, align_self);
                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Position type
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGPositionType position_type = YGNodeStyleGetPositionType(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Position type");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGPositionType_combo("##position_type", position_type) )
            {
                YGNodeStyleSetPositionType(node, position_type);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Flex wrap
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGWrap flex_wrap = YGNodeStyleGetFlexWrap(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex wrap");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGWrap_combo("##flex_wrap", flex_wrap) )
            {
                YGNodeStyleSetFlexWrap(node, flex_wrap);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Overflow
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGOverflow overflow = YGNodeStyleGetOverflow(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Overflow");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGOverflow_combo("##overflow", overflow) )
            {
                YGNodeStyleSetOverflow(node, overflow);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Display
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGDisplay display = YGNodeStyleGetDisplay(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Display");

            ImGui::TableNextColumn();
            if( ImGui_Yoga::YGDisplay_combo("##display", display) )
            {
                YGNodeStyleSetDisplay(node, display);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Flex
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            float flex = YGNodeStyleGetFlex(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex");

            ImGui::TableNextColumn();
            if( ImGui::InputScalar("##flex", ImGuiDataType_Float, &flex) )
            {
                YGNodeStyleSetFlex(node, flex);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Flex grow
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            float flex_grow = YGNodeStyleGetFlexGrow(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex grow");

            ImGui::TableNextColumn();
            if( ImGui::InputScalar("##flex_grow", ImGuiDataType_Float, &flex_grow) )
            {
                YGNodeStyleSetFlexGrow(node, flex_grow);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Flex shrink
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            float flex_shrink = YGNodeStyleGetFlexShrink(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex shrink");

            ImGui::TableNextColumn();
            if( ImGui::InputScalar("##flex_shrink", ImGuiDataType_Float, &flex_shrink) )
            {
                YGNodeStyleSetFlexShrink(node, flex_shrink);
                modified = true;
            }

            ImGui::EndTable();
        }

        // Flex basis
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            YGValue flex_basis = YGNodeStyleGetFlexBasis(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex basis");

            ImGui::TableNextColumn();

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

            ImGui::EndTable();
        }

        // Position
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd,
                YGEdge::YGEdgeHorizontal,
                YGEdge::YGEdgeVertical,
                YGEdge::YGEdgeAll
            })
            {
                YGValue position = YGNodeStyleGetPosition(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Position %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();

                const std::string tag = std::string("##position_") + YGEdgeToString(edge);
                if( ImGui_Yoga::YGValue_edit(tag.c_str(), position) )
                {
                    switch(position.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetPosition(node, edge, position.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetPositionPercent(node, edge, position.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetPosition(node, edge, YGUndefined); } break; // FIXME: maybe auto not needed

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetPosition(node, edge, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Margin
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd,
                YGEdge::YGEdgeHorizontal,
                YGEdge::YGEdgeVertical,
                YGEdge::YGEdgeAll
            })
            {
                YGValue margin = YGNodeStyleGetMargin(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Margin %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();

                const std::string tag = std::string("##margin_") + YGEdgeToString(edge);
                if( ImGui_Yoga::YGValue_edit(tag.c_str(), margin) )
                {
                    switch(margin.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMargin(node, edge, margin.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMarginPercent(node, edge, margin.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMarginAuto(node, edge); } break;

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMargin(node, edge, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Padding
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd,
                YGEdge::YGEdgeHorizontal,
                YGEdge::YGEdgeVertical,
                YGEdge::YGEdgeAll
            })
            {
                YGValue padding = YGNodeStyleGetPadding(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Padding %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();

                const std::string tag = std::string("##padding_") + YGEdgeToString(edge);
                if( ImGui_Yoga::YGValue_edit(tag.c_str(), padding) )
                {
                    switch(padding.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetPadding(node, edge, padding.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetPaddingPercent(node, edge, padding.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetPadding(node, edge, YGUndefined); } break; // FIXME: maybe auto not needed here

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetPadding(node, edge, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Border
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd,
                YGEdge::YGEdgeHorizontal,
                YGEdge::YGEdgeVertical,
                YGEdge::YGEdgeAll
            })
            {
                float border = YGNodeStyleGetBorder(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Border %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();

                const std::string tag = std::string("##border_") + YGEdgeToString(edge);
                if( ImGui::InputScalar(tag.c_str(), ImGuiDataType_Float, &border) )
                {
                    YGNodeStyleSetBorder(node, edge, border);

                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Gap
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            for(YGGutter gutter : {
                YGGutter::YGGutterColumn,
                YGGutter::YGGutterRow,
                YGGutter::YGGutterAll
            })
            {
                float gap = YGNodeStyleGetGap(node, gutter);

                ImGui::TableNextColumn();
                ImGui::Text("Gap %s", YGGutterToString(gutter));

                ImGui::TableNextColumn();

                const std::string tag = std::string("##gap_") + YGGutterToString(gutter);
                if( ImGui::InputScalar(tag.c_str(), ImGuiDataType_Float, &gap) )
                {
                    YGNodeStyleSetGap(node, gutter, gap);

                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Width, Height, Min Width, Min Height, Max Width, Max Height
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Width
            {
                YGValue width = YGNodeStyleGetWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Width");

                ImGui::TableNextColumn();

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

            // Height
            {
                YGValue height = YGNodeStyleGetHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Height");

                ImGui::TableNextColumn();

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

            // Min width
            {
                YGValue min_width = YGNodeStyleGetMinWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Min width");

                ImGui::TableNextColumn();

                if( ImGui_Yoga::YGValue_edit("##min_width", min_width) )
                {
                    switch(min_width.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMinWidth(node, min_width.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMinWidthPercent(node, min_width.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMinWidth(node, YGUndefined); } break; // FIXME: maybe auto not needed

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMinWidth(node, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            // Min height
            {
                YGValue min_height = YGNodeStyleGetMinHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Min height");

                ImGui::TableNextColumn();

                if( ImGui_Yoga::YGValue_edit("##min_height", min_height) )
                {
                    switch(min_height.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMinHeight(node, min_height.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMinHeightPercent(node, min_height.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMinHeight(node, YGUndefined); } break; // FIXME: maybe auto not needed

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMinHeight(node, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            // Max width
            {
                YGValue max_width = YGNodeStyleGetMaxWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Max width");

                ImGui::TableNextColumn();

                if( ImGui_Yoga::YGValue_edit("##max_width", max_width) )
                {
                    switch(max_width.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMaxWidth(node, max_width.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMaxWidthPercent(node, max_width.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMaxWidth(node, YGUndefined); } break; // FIXME: maybe auto not needed

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMaxWidth(node, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            // Max height
            {
                YGValue max_height = YGNodeStyleGetMaxHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Max height");

                ImGui::TableNextColumn();

                if( ImGui_Yoga::YGValue_edit("##max_height", max_height) )
                {
                    switch(max_height.unit) {
                    case YGUnit::YGUnitPoint:   { YGNodeStyleSetMaxHeight(node, max_height.value); } break;
                    case YGUnit::YGUnitPercent: { YGNodeStyleSetMaxHeightPercent(node, max_height.value); } break;
                    case YGUnit::YGUnitAuto:    { YGNodeStyleSetMaxHeight(node, YGUndefined); } break; // FIXME: maybe auto not needed

                    case YGUnit::YGUnitUndefined: { YGNodeStyleSetMaxHeight(node, YGUndefined); } break;
                    }

                    modified = true;
                }
            }

            ImGui::EndTable();
        }

        // Aspect ratio
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            float aspect_ratio = YGNodeStyleGetAspectRatio(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Aspect ratio");

            ImGui::TableNextColumn();
            if( ImGui::InputScalar("##aspect_ratio", ImGuiDataType_Float, &aspect_ratio) )
            {
                YGNodeStyleSetAspectRatio(node, aspect_ratio);
                modified = true;
            }

            ImGui::EndTable();
        }
    }

    ImGui::SeparatorText("Layout");
    {
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            {
                const float left = YGNodeLayoutGetLeft(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Left");

                ImGui::TableNextColumn();
                ImGui::Text("%f", left);
            }

            {
                const float top = YGNodeLayoutGetTop(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Top");

                ImGui::TableNextColumn();
                ImGui::Text("%f", top);
            }

            {
                const float right = YGNodeLayoutGetRight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Right");

                ImGui::TableNextColumn();
                ImGui::Text("%f", right);
            }

            {
                const float bottom = YGNodeLayoutGetBottom(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Bottom");

                ImGui::TableNextColumn();
                ImGui::Text("%f", bottom);
            }

            {
                const float width = YGNodeLayoutGetWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Width");

                ImGui::TableNextColumn();
                ImGui::Text("%f", width);
            }

            {
                const float height = YGNodeLayoutGetHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Height");

                ImGui::TableNextColumn();
                ImGui::Text("%f", height);
            }

            {
                const YGDirection direction = YGNodeLayoutGetDirection(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Direction");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted( YGDirectionToString(direction) );
            }

            ImGui::EndTable();
        }

        // Margin
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Only [Left, Top, Right, Bottom, Start, End], since [Horizontal, Vertical, All]
            // produces std::logic_error :: "Cannot get layout properties of multi-edge shorthands"
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd
            })
            {
                const float margin = YGNodeLayoutGetMargin(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Margin %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui::Text("%f", margin);
            }

            ImGui::EndTable();
        }

        // Border
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Only [Left, Top, Right, Bottom, Start, End], since [Horizontal, Vertical, All]
            // produces std::logic_error :: "Cannot get layout properties of multi-edge shorthands"
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd
            })
            {
                const float border = YGNodeLayoutGetBorder(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Border %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui::Text("%f", border);
            }

            ImGui::EndTable();
        }

        // Padding
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Only [Left, Top, Right, Bottom, Start, End], since [Horizontal, Vertical, All]
            // produces std::logic_error :: "Cannot get layout properties of multi-edge shorthands"
            for(YGEdge edge : {
                YGEdge::YGEdgeLeft,
                YGEdge::YGEdgeTop,
                YGEdge::YGEdgeRight,
                YGEdge::YGEdgeBottom,
                YGEdge::YGEdgeStart,
                YGEdge::YGEdgeEnd
            })
            {
                const float padding = YGNodeLayoutGetPadding(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Padding %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui::Text("%f", padding);
            }

            ImGui::EndTable();
        }
    }

    return modified;
}
