#include <ImGui_Yoga/YGNode_inspect_web.hpp>

#include <imgui.h>

#include <ImGui_Yoga/enums.hpp>
#include <ImGui_Yoga/YGValue_widgets.hpp>

#include <ImGui_Yoga/utility_widgets.hpp>

void ImGui_Yoga::YGNode_inspect_web(YGNodeConstRef node)
{
    if(node == nullptr)
    {
        return;
    }

    // NOTE: Due to missing constness in public C API, we need to use non-const
    // pointer sometimes.
    YGNodeRef n = const_cast<YGNodeRef>(node);

    const ImVec2 SEPARATOR_RECT = {0.0f, ImGui::GetFontSize() / 2.0f };

    const bool is_root = (YGNodeGetParent(n) == nullptr);

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

                const YGDirection direction = YGNodeStyleGetDirection(node);

                ImGui::TextUnformatted(YGDirectionToString(direction));
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Flex Direction
            {
                ImGui::TextUnformatted("FLEX DIRECTION");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Defines the direction of the main-axis");

                const YGFlexDirection flex_direction = YGNodeStyleGetFlexDirection(node);

                ImGui::TextUnformatted(YGFlexDirectionToString(flex_direction));
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

                    const YGValue flex_basis = YGNodeStyleGetFlexBasis(node);

                    if(is_root)
                    {
                        ImGui_Yoga::YGValue_text_disabled(flex_basis);
                    }
                    else
                    {
                        ImGui_Yoga::YGValue_text(flex_basis);
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

                    const float flex_grow = YGNodeStyleGetFlexGrow(node);

                    if(is_root)
                    {
                        ImGui::TextDisabled("%f", flex_grow);
                    }
                    else
                    {
                        ImGui::Text("%f", flex_grow);
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

                    const float flex_shrink = YGNodeStyleGetFlexShrink(node);

                    if(is_root)
                    {
                        ImGui::TextDisabled("%f", flex_shrink);
                    }
                    else
                    {
                        ImGui::Text("%f", flex_shrink);
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

                const YGWrap flex_wrap = YGNodeStyleGetFlexWrap(node);

                ImGui::TextUnformatted(YGWrapToString(flex_wrap));
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

                const YGJustify justify_content = YGNodeStyleGetJustifyContent(node);

                ImGui::TextUnformatted(YGJustifyToString(justify_content));
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Align items
            {
                ImGui::TextUnformatted("ALIGN ITEMS");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Aligns child nodes along the cross-axis");

                const YGAlign align_items = YGNodeStyleGetAlignItems(node);

                ImGui::TextUnformatted(YGAlignToString(align_items));
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Align self
            {
                ImGui::TextUnformatted("ALIGN SELF");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Override align items of parent");

                const YGAlign align_self = YGNodeStyleGetAlignSelf(node);

                if(is_root)
                {
                    ImGui::TextDisabled("%s", YGAlignToString(align_self) );
                }
                else
                {
                    ImGui::TextUnformatted(YGAlignToString(align_self));
                }

            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Align content
            {
                ImGui::TextUnformatted("ALIGN CONTENT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Alignment of lines along the cross-axis when wrapping");

                const YGAlign align_content = YGNodeStyleGetAlignContent(node);

                ImGui::TextUnformatted(YGAlignToString(align_content));
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
                    const YGValue width  = YGNodeStyleGetWidth(node);

                    ImGui_Yoga::YGValue_text(width);
                }

                ImGui::SameLine();

                {
                    const YGValue height = YGNodeStyleGetHeight(node);

                    ImGui_Yoga::YGValue_text(height);
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Max-width x Max-height
            {
                ImGui::TextUnformatted("MAX-WIDTH x MAX-HEIGHT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Maximum dimensions of the node");

                {
                    const YGValue max_width  = YGNodeStyleGetMaxWidth(node);

                    ImGui_Yoga::YGValue_text(max_width);
                }

                ImGui::SameLine();

                {
                    const YGValue max_height = YGNodeStyleGetMaxHeight(node);

                    ImGui_Yoga::YGValue_text(max_height);
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Min-width x Min-height
            {
                ImGui::TextUnformatted("MIN-WIDTH x MIN-HEIGHT");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Minimum dimensions of the node");

                {
                    const YGValue min_width  = YGNodeStyleGetMinWidth(node);

                    ImGui_Yoga::YGValue_text(min_width);
                }

                ImGui::SameLine();

                {
                    const YGValue min_height = YGNodeStyleGetMinHeight(node);

                    ImGui_Yoga::YGValue_text(min_height);
                }
            }

            ImGui::Dummy(SEPARATOR_RECT); // Separator

            // Aspect ratio
            {
                ImGui::TextUnformatted("ASPECT RATIO");
                ImGui::SameLine();
                ImGui_Yoga::HelpMarker("Width/Height aspect ratio of node");

                const float aspect_ratio = YGNodeStyleGetAspectRatio(node);

                ImGui::Text("%f", aspect_ratio);
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

                            const YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            ImGui_Yoga::YGValue_text(padding);
                        }
                    }

                    // Middle row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(0);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeLeft;

                            const YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            ImGui_Yoga::YGValue_text(padding);
                        }

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("PADDING");

                        ImGui::TableSetColumnIndex(2);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeRight;

                            const YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            ImGui_Yoga::YGValue_text(padding);
                        }
                    }

                    // Bottom row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge PADDIGN_SIDE = YGEdge::YGEdgeBottom;

                            const YGValue padding = YGNodeStyleGetPadding(node, PADDIGN_SIDE);

                            ImGui_Yoga::YGValue_text(padding);
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

                            const float border = YGNodeStyleGetBorder(node, BORDER_SIDE);

                            ImGui::Text("%f", border);
                        }
                    }

                    // Middle row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(0);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeLeft;

                            const float border = YGNodeStyleGetBorder(node, BORDER_SIDE);

                            ImGui::Text("%f", border);
                        }

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("BORDER");

                        ImGui::TableSetColumnIndex(2);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeRight;

                            const float border = YGNodeStyleGetBorder(node, BORDER_SIDE);

                            ImGui::Text("%f", border);
                        }
                    }

                    // Bottom row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge BORDER_SIDE = YGEdge::YGEdgeBottom;

                            const float border = YGNodeStyleGetBorder(node, BORDER_SIDE);

                            ImGui::Text("%f", border);
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

                            const YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                ImGui_Yoga::YGValue_text(margin);
                            }
                        }
                    }

                    // Middle row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(0);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeLeft;

                            const YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                ImGui_Yoga::YGValue_text(margin);
                            }
                        }

                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("MARGIN");

                        ImGui::TableSetColumnIndex(2);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeRight;

                            const YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                ImGui_Yoga::YGValue_text(margin);
                            }
                        }
                    }

                    // Bottom row --------------------------------------
                    ImGui::TableNextRow();
                    {
                        ImGui::TableSetColumnIndex(1);
                        {
                            constexpr YGEdge MARGIN_SIDE = YGEdge::YGEdgeBottom;

                            const YGValue margin = YGNodeStyleGetMargin(node, MARGIN_SIDE);

                            if(is_root)
                            {
                                ImGui_Yoga::YGValue_text_disabled(margin);
                            }
                            else
                            {
                                ImGui_Yoga::YGValue_text(margin);
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
                    const YGPositionType pos_type = YGNodeStyleGetPositionType(node);

                    if(is_root)
                    {
                        ImGui::TextDisabled("%s", YGPositionTypeToString(pos_type) );
                    }
                    else
                    {
                        ImGui::TextUnformatted( YGPositionTypeToString(pos_type) );
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

                                const YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                ImGui_Yoga::YGValue_text(position);
                            }
                        }

                        // Middle row --------------------------------------
                        ImGui::TableNextRow();
                        {
                            ImGui::TableSetColumnIndex(0);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeLeft;

                                const YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                ImGui_Yoga::YGValue_text(position);
                            }

                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text("POSITION");

                            ImGui::TableSetColumnIndex(2);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeRight;

                                const YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                ImGui_Yoga::YGValue_text(position);
                            }
                        }

                        // Bottom row --------------------------------------
                        ImGui::TableNextRow();
                        {
                            ImGui::TableSetColumnIndex(1);
                            {
                                constexpr YGEdge POS_SIDE = YGEdge::YGEdgeBottom;

                                const YGValue position = YGNodeStyleGetPosition(node, POS_SIDE);

                                ImGui_Yoga::YGValue_text(position);
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
}
