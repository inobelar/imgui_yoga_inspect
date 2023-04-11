#include <ImGui_Yoga/YGNode_inspect_full.hpp>

#include <imgui.h>

#include <ImGui_Yoga/enums.hpp>
#include <ImGui_Yoga/YGValue_widgets.hpp>

#include <string>

void ImGui_Yoga::YGNode_inspect_full(YGNodeConstRef node)
{
    if(node == nullptr)
    {
        return;
    }

    // NOTE: Due to missing constness in public C API, we need to use non-const
    // pointer sometimes.
    YGNodeRef n = const_cast<YGNodeRef>(node);

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
            const YGNodeRef parent = YGNodeGetParent(n);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Parent");

            ImGui::TableNextColumn();
            ImGui::Text("%p", parent);

            ImGui::EndTable();
        }

        // Childs
        {
            const uint32_t child_count = YGNodeGetChildCount(n);

            if(child_count > 0)
            {
                if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
                {
                    for(uint32_t child_idx = 0; child_idx < child_count; ++child_idx)
                    {
                        const YGNodeRef child = YGNodeGetChild(n, child_idx);

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
            const bool is_reference_baseline = YGNodeIsReferenceBaseline(n);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Is Reference Baseline");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(is_reference_baseline ? "true" : "false");

            ImGui::EndTable();
        }

        // Dirty
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const bool is_dirty = YGNodeIsDirty(n);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Is dirty");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(is_dirty ? "true" : "false");

            ImGui::EndTable();
        }

        // Context
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const void* context = YGNodeGetContext(n);

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
                ImGui::TextUnformatted(YGNodeHasMeasureFunc(n) ? "true" : "false");
            }

            // Baseline
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Has baseline func");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted(YGNodeHasBaselineFunc(n) ? "true" : "false");
            }

            // Dirtied
            {
                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Has dirtied func");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted((YGNodeGetDirtiedFunc(n) != nullptr) ? "true" : "false");
            }

            ImGui::EndTable();
        }

        // New layout
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const bool has_new_layout = YGNodeGetHasNewLayout(n);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Has new layout");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(has_new_layout ? "true" : "false");

            ImGui::EndTable();
        }

        // Node type
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGNodeType node_type = YGNodeGetNodeType(n);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Node type");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGNodeTypeToString(node_type));

            ImGui::EndTable();
        }
    }

    ImGui::SeparatorText("Style");
    {
        // Direction
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGDirection direction = YGNodeStyleGetDirection(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Direction");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGDirectionToString(direction));

            ImGui::EndTable();
        }

        // Flex Direction
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGFlexDirection flex_direction = YGNodeStyleGetFlexDirection(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex direction");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGFlexDirectionToString(flex_direction));

            ImGui::EndTable();
        }

        // Justify content
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGJustify justify_content = YGNodeStyleGetJustifyContent(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Justify content");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGJustifyToString(justify_content));

            ImGui::EndTable();
        }

        // Align
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Content
            {
                const YGAlign align_content = YGNodeStyleGetAlignContent(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align content");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted(YGAlignToString(align_content));
            }

            // Items
            {
                const YGAlign align_items = YGNodeStyleGetAlignItems(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align items");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted(YGAlignToString(align_items));
            }

            // Self
            {
                const YGAlign align_self = YGNodeStyleGetAlignSelf(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Align self");

                ImGui::TableNextColumn();
                ImGui::TextUnformatted(YGAlignToString(align_self));
            }

            ImGui::EndTable();
        }

        // Position type
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGPositionType position_type = YGNodeStyleGetPositionType(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Position type");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGPositionTypeToString(position_type));

            ImGui::EndTable();
        }

        // Flex wrap
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGWrap flex_wrap = YGNodeStyleGetFlexWrap(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex wrap");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGWrapToString(flex_wrap));

            ImGui::EndTable();
        }

        // Overflow
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGOverflow overflow = YGNodeStyleGetOverflow(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Overflow");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGOverflowToString(overflow));

            ImGui::EndTable();
        }

        // Display
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGDisplay display = YGNodeStyleGetDisplay(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Display");

            ImGui::TableNextColumn();
            ImGui::TextUnformatted(YGDisplayToString(display));

            ImGui::EndTable();
        }

        // Flex
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const float flex = YGNodeStyleGetFlex(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex");

            ImGui::TableNextColumn();
            ImGui::Text("%f", flex);

            ImGui::EndTable();
        }

        // Flex grow
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const float flex_grow = YGNodeStyleGetFlexGrow(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex grow");

            ImGui::TableNextColumn();
            ImGui::Text("%f", flex_grow);

            ImGui::EndTable();
        }

        // Flex shrink
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const float flex_shrink = YGNodeStyleGetFlexShrink(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex shrink");

            ImGui::TableNextColumn();
            ImGui::Text("%f", flex_shrink);

            ImGui::EndTable();
        }

        // Flex basis
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const YGValue flex_basis = YGNodeStyleGetFlexBasis(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Flex basis");

            ImGui::TableNextColumn();
            ImGui_Yoga::YGValue_text(flex_basis);

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
                const YGValue position = YGNodeStyleGetPosition(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Position %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(position);
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
                const YGValue margin = YGNodeStyleGetMargin(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Margin %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(margin);
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
                const YGValue padding = YGNodeStyleGetPadding(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Padding %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(padding);
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
                const float border = YGNodeStyleGetBorder(node, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Border %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui::Text("%f", border);
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
                const float gap = YGNodeStyleGetGap(node, gutter);

                ImGui::TableNextColumn();
                ImGui::Text("Gap %s", YGGutterToString(gutter));

                ImGui::TableNextColumn();
                ImGui::Text("%f", gap);
            }

            ImGui::EndTable();
        }

        // Width, Height, Min Width, Min Height, Max Width, Max Height
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            // Width
            {
                const YGValue width = YGNodeStyleGetWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Width");

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(width);
            }

            // Height
            {
                const YGValue height = YGNodeStyleGetHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Height");

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(height);
            }

            // Min width
            {
                const YGValue min_width = YGNodeStyleGetMinWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Min width");

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(min_width);
            }

            // Min height
            {
                const YGValue min_height = YGNodeStyleGetMinHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Min height");

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(min_height);
            }

            // Max width
            {
                const YGValue max_width = YGNodeStyleGetMaxWidth(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Max width");

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(max_width);
            }

            // Max height
            {
                const YGValue max_height = YGNodeStyleGetMaxHeight(node);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Max height");

                ImGui::TableNextColumn();
                ImGui_Yoga::YGValue_text(max_height);
            }

            ImGui::EndTable();
        }

        // Aspect ratio
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            const float aspect_ratio = YGNodeStyleGetAspectRatio(node);

            ImGui::TableNextColumn();
            ImGui::TextUnformatted("Aspect ratio");

            ImGui::TableNextColumn();
            ImGui::Text("%f", aspect_ratio);

            ImGui::EndTable();
        }
    }

    ImGui::SeparatorText("Layout");
    {
        if( ImGui::BeginTable(TABLE_ID, 2, TABLE_FLAGS) )
        {
            {
                const float left = YGNodeLayoutGetLeft(n);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Left");

                ImGui::TableNextColumn();
                ImGui::Text("%f", left);
            }

            {
                const float top = YGNodeLayoutGetTop(n);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Top");

                ImGui::TableNextColumn();
                ImGui::Text("%f", top);
            }

            {
                const float right = YGNodeLayoutGetRight(n);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Right");

                ImGui::TableNextColumn();
                ImGui::Text("%f", right);
            }

            {
                const float bottom = YGNodeLayoutGetBottom(n);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Bottom");

                ImGui::TableNextColumn();
                ImGui::Text("%f", bottom);
            }

            {
                const float width = YGNodeLayoutGetWidth(n);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Width");

                ImGui::TableNextColumn();
                ImGui::Text("%f", width);
            }

            {
                const float height = YGNodeLayoutGetHeight(n);

                ImGui::TableNextColumn();
                ImGui::TextUnformatted("Height");

                ImGui::TableNextColumn();
                ImGui::Text("%f", height);
            }

            {
                const YGDirection direction = YGNodeLayoutGetDirection(n);

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
                const float margin = YGNodeLayoutGetMargin(n, edge);

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
                const float border = YGNodeLayoutGetBorder(n, edge);

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
                const float padding = YGNodeLayoutGetPadding(n, edge);

                ImGui::TableNextColumn();
                ImGui::Text("Padding %s", YGEdgeToString(edge));

                ImGui::TableNextColumn();
                ImGui::Text("%f", padding);
            }

            ImGui::EndTable();
        }
    }

}
