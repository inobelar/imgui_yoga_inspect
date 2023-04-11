#include <ImGui_Yoga/enums.hpp>

#include <imgui.h>

/*
    Note about 'YGPrintOptions', which is not enumeration, but bit flags.

    Unfortunately, we cannot use bit operations over enum, for example,
    naive code below:

        @code{.cpp}
            YGPrintOptions options;
            options |= YGPrintOptions::YGPrintOptionsLayout;
        @endcode

    not compiles, since next error (on GCC):

        assigning to 'YGPrintOptions' from incompatible type 'int'.

    so we must use extra 'raw' integer variable, over which we do bit
    operations, and after them - assign it into 'enum':

        @code{.cpp}
            YGPrintOptions options;
            int options_raw = options;
            options_raw |= YGPrintOptions::YGPrintOptionsLayout;
            options = static_cast<YGPrintOptions>(options_raw);
        @endcode

    Reference about bit flags setting:
        https://stackoverflow.com/a/2574574/
*/

// -----------------------------------------------------------------------------

bool ImGui_Yoga::YGAlign_combo(const char* label, YGAlign& align)
{
    constexpr YGAlign ALIGNS[]
    {
        YGAlign::YGAlignAuto,
        YGAlign::YGAlignFlexStart,
        YGAlign::YGAlignCenter,
        YGAlign::YGAlignFlexEnd,
        YGAlign::YGAlignStretch,
        YGAlign::YGAlignBaseline,
        YGAlign::YGAlignSpaceBetween,
        YGAlign::YGAlignSpaceAround
    };

    bool modified = false;

    const char* combo_label = YGAlignToString(align);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGAlign align_to_choose : ALIGNS)
        {
            const bool is_selected = (align_to_choose == align);

            const char* selectable_label = YGAlignToString(align_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                align = align_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGDimension_combo(const char* label, YGDimension& dimention)
{
    constexpr YGDimension DIMENSIONS[]
    {
        YGDimension::YGDimensionWidth,
        YGDimension::YGDimensionHeight,
    };

    bool modified = false;

    const char* combo_label = YGDimensionToString(dimention);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGDimension dimension_to_choose : DIMENSIONS)
        {
            const bool is_selected = (dimension_to_choose == dimention);

            const char* selectable_label = YGDimensionToString(dimension_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                dimention = dimension_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGDimension_radio(YGDimension& dimension)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGDimension DIMENSION = YGDimension::YGDimensionWidth;
            if( ImGui::RadioButton( YGDimensionToString(DIMENSION), (dimension == DIMENSION)) )
            {
                dimension = DIMENSION;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGDimension DIMENSION = YGDimension::YGDimensionHeight;
            if( ImGui::RadioButton( YGDimensionToString(DIMENSION), (dimension == DIMENSION)) )
            {
                dimension = DIMENSION;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGDirection_combo(const char* label, YGDirection& direction)
{
    constexpr YGDirection DIRECTIONS[]
    {
        YGDirection::YGDirectionInherit,
        YGDirection::YGDirectionLTR,
        YGDirection::YGDirectionRTL
    };

    bool modified = false;

    const char* combo_label = YGDirectionToString(direction);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGDirection direction_to_choose : DIRECTIONS)
        {
            const bool is_selected = (direction_to_choose == direction);

            const char* selectable_label = YGDirectionToString(direction_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                direction = direction_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGDirection_radio(YGDirection& direction)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGDirection DIRECTION = YGDirection::YGDirectionInherit;
            if( ImGui::RadioButton( YGDirectionToString(DIRECTION), (direction == DIRECTION)) )
            {
                direction = DIRECTION;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGDirection DIRECTION = YGDirection::YGDirectionLTR;
            if( ImGui::RadioButton( YGDirectionToString(DIRECTION), (direction == DIRECTION)) )
            {
                direction = DIRECTION;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGDirection DIRECTION = YGDirection::YGDirectionRTL;
            if( ImGui::RadioButton( YGDirectionToString(DIRECTION), (direction == DIRECTION)) )
            {
                direction = DIRECTION;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGDisplay_combo(const char* label, YGDisplay& display)
{
    constexpr YGDisplay DISPLAYS[]
    {
        YGDisplay::YGDisplayFlex,
        YGDisplay::YGDisplayNone,
    };

    bool modified = false;

    const char* combo_label = YGDisplayToString(display);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGDisplay display_to_choose : DISPLAYS)
        {
            const bool is_selected = (display_to_choose == display);

            const char* selectable_label = YGDisplayToString(display_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                display = display_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGDisplay_radio(YGDisplay& display)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGDisplay DISPLAY = YGDisplay::YGDisplayFlex;
            if( ImGui::RadioButton( YGDisplayToString(DISPLAY), (display == DISPLAY)) )
            {
                display = DISPLAY;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGDisplay DISPLAY = YGDisplay::YGDisplayNone;
            if( ImGui::RadioButton( YGDisplayToString(DISPLAY), (display == DISPLAY)) )
            {
                display = DISPLAY;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGEdge_combo(const char* label, YGEdge& edge)
{
    constexpr YGEdge EDGES[]
    {
        YGEdge::YGEdgeLeft,
        YGEdge::YGEdgeTop,
        YGEdge::YGEdgeRight,
        YGEdge::YGEdgeBottom,
        YGEdge::YGEdgeStart,
        YGEdge::YGEdgeEnd,
        YGEdge::YGEdgeHorizontal,
        YGEdge::YGEdgeVertical,
        YGEdge::YGEdgeAll
    };

    bool modified = false;

    const char* combo_label = YGEdgeToString(edge);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGEdge edge_to_choose : EDGES)
        {
            const bool is_selected = (edge_to_choose == edge);

            const char* selectable_label = YGEdgeToString(edge_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                edge = edge_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGFlexDirection_combo(const char* label, YGFlexDirection& flex_direction)
{
    constexpr YGFlexDirection FLEX_DIRECTIONS[]
    {
        YGFlexDirection::YGFlexDirectionColumn,
        YGFlexDirection::YGFlexDirectionColumnReverse,
        YGFlexDirection::YGFlexDirectionRow,
        YGFlexDirection::YGFlexDirectionRowReverse
    };

    bool modified = false;

    const char* combo_label = YGFlexDirectionToString(flex_direction);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGFlexDirection flex_dir_to_choose : FLEX_DIRECTIONS)
        {
            const bool is_selected = (flex_dir_to_choose == flex_direction);

            const char* selectable_label = YGFlexDirectionToString(flex_dir_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                flex_direction = flex_dir_to_choose;
                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGGutter_combo(const char* label, YGGutter& gutter)
{
    constexpr YGGutter GUTTERS[]
    {
        YGGutter::YGGutterColumn,
        YGGutter::YGGutterRow,
        YGGutter::YGGutterAll
    };

    bool modified = false;

    const char* combo_label = YGGutterToString(gutter);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGGutter gutter_to_choose : GUTTERS)
        {
            const bool is_selected = (gutter_to_choose == gutter);

            const char* selectable_label = YGGutterToString(gutter_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                gutter = gutter_to_choose;
                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGGutter_radio(YGGutter& gutter)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGGutter GUTTER = YGGutter::YGGutterColumn;
            if( ImGui::RadioButton( YGGutterToString(GUTTER), (gutter == GUTTER)) )
            {
                gutter = GUTTER;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGGutter GUTTER = YGGutter::YGGutterRow;
            if( ImGui::RadioButton( YGGutterToString(GUTTER), (gutter == GUTTER)) )
            {
                gutter = GUTTER;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGGutter GUTTER = YGGutter::YGGutterAll;
            if( ImGui::RadioButton( YGGutterToString(GUTTER), (gutter == GUTTER)) )
            {
                gutter = GUTTER;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGJustify_combo(const char* label, YGJustify& justification)
{
    constexpr YGJustify JUSTIFIES[]
    {
        YGJustify::YGJustifyFlexStart,
        YGJustify::YGJustifyCenter,
        YGJustify::YGJustifyFlexEnd,
        YGJustify::YGJustifySpaceBetween,
        YGJustify::YGJustifySpaceAround,
        YGJustify::YGJustifySpaceEvenly
    };

    bool modified = false;

    const char* combo_label = YGJustifyToString(justification);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGJustify justify_to_choose : JUSTIFIES)
        {
            const bool is_selected = (justify_to_choose == justification);

            const char* selectable_label = YGJustifyToString(justify_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                justification = justify_to_choose;
                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGLogLevel_combo(const char* label, YGLogLevel& log_level)
{
    constexpr YGLogLevel LOG_LEVELS[]
    {
        YGLogLevel::YGLogLevelError,
        YGLogLevel::YGLogLevelWarn,
        YGLogLevel::YGLogLevelInfo,
        YGLogLevel::YGLogLevelDebug,
        YGLogLevel::YGLogLevelVerbose,
        YGLogLevel::YGLogLevelFatal
    };

    bool modified = false;

    const char* combo_label = YGLogLevelToString(log_level);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGLogLevel log_level_to_choose : LOG_LEVELS)
        {
            const bool is_selected = (log_level_to_choose == log_level);

            const char* selectable_label = YGLogLevelToString(log_level_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                log_level = log_level_to_choose;
                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGMeasureMode_combo(const char* label, YGMeasureMode& measure_mode)
{
    constexpr YGMeasureMode MEASURE_MODES[]
    {
        YGMeasureMode::YGMeasureModeUndefined,
        YGMeasureMode::YGMeasureModeExactly,
        YGMeasureMode::YGMeasureModeAtMost,
    };

    bool modified = false;

    const char* combo_label = YGMeasureModeToString(measure_mode);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGMeasureMode measure_mode_to_choose : MEASURE_MODES)
        {
            const bool is_selected = (measure_mode_to_choose == measure_mode);

            const char* selectable_label = YGMeasureModeToString(measure_mode_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                measure_mode = measure_mode_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGMeasureMode_radio(YGMeasureMode& measure_mode)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGMeasureMode MEASURE_MODE = YGMeasureMode::YGMeasureModeUndefined;
            if( ImGui::RadioButton( YGMeasureModeToString(MEASURE_MODE), (measure_mode == MEASURE_MODE)) )
            {
                measure_mode = MEASURE_MODE;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGMeasureMode MEASURE_MODE = YGMeasureMode::YGMeasureModeExactly;
            if( ImGui::RadioButton( YGMeasureModeToString(MEASURE_MODE), (measure_mode == MEASURE_MODE)) )
            {
                measure_mode = MEASURE_MODE;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGMeasureMode MEASURE_MODE = YGMeasureMode::YGMeasureModeAtMost;
            if( ImGui::RadioButton( YGMeasureModeToString(MEASURE_MODE), (measure_mode == MEASURE_MODE)) )
            {
                measure_mode = MEASURE_MODE;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGNodeType_combo(const char* label, YGNodeType& node_type)
{
    constexpr YGNodeType NODE_TYPES[]
    {
        YGNodeType::YGNodeTypeDefault,
        YGNodeType::YGNodeTypeText,
    };

    bool modified = false;

    const char* combo_label = YGNodeTypeToString(node_type);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGNodeType node_type_to_choose : NODE_TYPES)
        {
            const bool is_selected = (node_type_to_choose == node_type);

            const char* selectable_label = YGNodeTypeToString(node_type_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                node_type = node_type_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGNodeType_radio(YGNodeType& node_type)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGNodeType NODE_TYPE = YGNodeType::YGNodeTypeDefault;
            if( ImGui::RadioButton( YGNodeTypeToString(NODE_TYPE), (node_type == NODE_TYPE)) )
            {
                node_type = NODE_TYPE;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGNodeType NODE_TYPE = YGNodeType::YGNodeTypeText;
            if( ImGui::RadioButton( YGNodeTypeToString(NODE_TYPE), (node_type == NODE_TYPE)) )
            {
                node_type = NODE_TYPE;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGOverflow_combo(const char* label, YGOverflow& overflow)
{
    constexpr YGOverflow OVERFLOWS[]
    {
        YGOverflow::YGOverflowVisible,
        YGOverflow::YGOverflowHidden,
        YGOverflow::YGOverflowScroll,
    };

    bool modified = false;

    const char* combo_label = YGOverflowToString(overflow);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGOverflow overflow_to_choose : OVERFLOWS)
        {
            const bool is_selected = (overflow_to_choose == overflow);

            const char* selectable_label = YGOverflowToString(overflow_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                overflow = overflow_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGOverflow_radio(YGOverflow& overflow)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGOverflow OVERFLOW = YGOverflow::YGOverflowVisible;
            if( ImGui::RadioButton( YGOverflowToString(OVERFLOW), (overflow == OVERFLOW)) )
            {
                overflow = OVERFLOW;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGOverflow OVERFLOW = YGOverflow::YGOverflowHidden;
            if( ImGui::RadioButton( YGOverflowToString(OVERFLOW), (overflow == OVERFLOW)) )
            {
                overflow = OVERFLOW;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGOverflow OVERFLOW = YGOverflow::YGOverflowScroll;
            if( ImGui::RadioButton( YGOverflowToString(OVERFLOW), (overflow == OVERFLOW)) )
            {
                overflow = OVERFLOW;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGPositionType_combo(const char* label, YGPositionType& pos_type)
{
    constexpr YGPositionType POS_TYPES[]
    {
        YGPositionType::YGPositionTypeStatic,
        YGPositionType::YGPositionTypeRelative,
        YGPositionType::YGPositionTypeAbsolute
    };

    bool modified = false;

    const char* combo_label = YGPositionTypeToString(pos_type);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGPositionType pos_type_to_choose : POS_TYPES)
        {
            const bool is_selected = (pos_type_to_choose == pos_type);

            const char* selectable_label = YGPositionTypeToString(pos_type_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                pos_type = pos_type_to_choose;
                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGPositionType_radio(YGPositionType& pos_type)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGPositionType POS_TYPE = YGPositionType::YGPositionTypeStatic;
            if( ImGui::RadioButton( YGPositionTypeToString(POS_TYPE), (pos_type == POS_TYPE)) )
            {
                pos_type = POS_TYPE;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            {
                constexpr YGPositionType POS_TYPE = YGPositionType::YGPositionTypeRelative;
                if( ImGui::RadioButton( YGPositionTypeToString(POS_TYPE), (pos_type == POS_TYPE)) )
                {
                    pos_type = POS_TYPE;
                    modified = true;
                }
            }
        }

        ImGui::SameLine();

        {
            {
                constexpr YGPositionType POS_TYPE = YGPositionType::YGPositionTypeAbsolute;
                if( ImGui::RadioButton( YGPositionTypeToString(POS_TYPE), (pos_type == POS_TYPE)) )
                {
                    pos_type = POS_TYPE;
                    modified = true;
                }
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

bool ImGui_Yoga::YGPrintOptions_combo(const char* label, YGPrintOptions& print_options)
{
    static const auto YGPrintOptions_combo_raw = [](const char* label, int& print_options_raw) -> bool
    {
        static const auto is_option_enabled = [](const int& opt_raw, const YGPrintOptions& flag) -> bool
        {
            return (opt_raw & flag) != 0;
        };

        constexpr YGPrintOptions PRINT_OPTIONS[]
        {
            YGPrintOptions::YGPrintOptionsLayout,
            YGPrintOptions::YGPrintOptionsStyle,
            YGPrintOptions::YGPrintOptionsChildren
        };

        bool modified = false;

        constexpr size_t TEXT_BUFFFER_SIZE = 64;
        static char TEXT_BUFFER[TEXT_BUFFFER_SIZE];
        snprintf(TEXT_BUFFER, TEXT_BUFFFER_SIZE, "%s:%s %s:%s %s:%s",
                 YGPrintOptionsToString(YGPrintOptions::YGPrintOptionsLayout),
                 (is_option_enabled(print_options_raw, YGPrintOptions::YGPrintOptionsLayout) ? "true" : "false"),

                 YGPrintOptionsToString(YGPrintOptions::YGPrintOptionsStyle),
                 (is_option_enabled(print_options_raw, YGPrintOptions::YGPrintOptionsStyle) ? "true" : "false"),

                 YGPrintOptionsToString(YGPrintOptions::YGPrintOptionsChildren),
                 (is_option_enabled(print_options_raw, YGPrintOptions::YGPrintOptionsChildren) ? "true" : "false")
        );

        const char* combo_label = TEXT_BUFFER;

        if (ImGui::BeginCombo(label, combo_label))
        {
            for (const YGPrintOptions option_to_choose : PRINT_OPTIONS)
            {
                bool option_enabled = is_option_enabled(print_options_raw, option_to_choose);

                if( ImGui::Checkbox( YGPrintOptionsToString(option_to_choose), &option_enabled) )
                {
                    if(option_enabled)
                    {
                        print_options_raw |=  option_to_choose; // Set flag
                    }
                    else
                    {
                        print_options_raw &= ~option_to_choose; // Unset flag
                    }

                    modified = true;
                }
            }

            ImGui::EndCombo();
        }

        return modified;
    };

    // -------------------------------------------------------------------------

    int print_options_raw = print_options;

    const bool modified = YGPrintOptions_combo_raw(label, print_options_raw);

    if(modified)
    {
        // Assign raw value into enum
        print_options = static_cast<YGPrintOptions>(print_options_raw);
    }

    return modified;
}

bool ImGui_Yoga::YGPrintOptions_checkboxes(YGPrintOptions& print_options)
{
    static const auto YGPrintOptions_checkboxes_raw = [](int& print_options_raw) -> bool
    {
        bool modified = false;

        ImGui::BeginGroup();
        {
            {
                constexpr YGPrintOptions PRINT_OPTION = YGPrintOptions::YGPrintOptionsLayout;

                bool option_enabled = (print_options_raw & PRINT_OPTION) != 0; // Is flag set
                if( ImGui::Checkbox( YGPrintOptionsToString(PRINT_OPTION), &option_enabled) )
                {
                    if(option_enabled)
                    {
                        print_options_raw |=  PRINT_OPTION; // Set flag
                    }
                    else
                    {
                        print_options_raw &= ~PRINT_OPTION; // Unset flag
                    }

                    modified = true;
                }
            }

            ImGui::SameLine();

            {
                constexpr YGPrintOptions PRINT_OPTION = YGPrintOptions::YGPrintOptionsStyle;

                bool option_enabled = (print_options_raw & PRINT_OPTION) != 0; // Is flag set
                if( ImGui::Checkbox( YGPrintOptionsToString(PRINT_OPTION), &option_enabled) )
                {
                    if(option_enabled)
                    {
                        print_options_raw |=  PRINT_OPTION; // Set flag
                    }
                    else
                    {
                        print_options_raw &= ~PRINT_OPTION; // Unset flag
                    }

                    modified = true;
                }
            }

            ImGui::SameLine();

            {
                constexpr YGPrintOptions PRINT_OPTION = YGPrintOptions::YGPrintOptionsChildren;

                bool option_enabled = (print_options_raw & PRINT_OPTION) != 0; // Is flag set
                if( ImGui::Checkbox( YGPrintOptionsToString(PRINT_OPTION), &option_enabled) )
                {
                    if(option_enabled)
                    {
                        print_options_raw |=  PRINT_OPTION; // Set flag
                    }
                    else
                    {
                        print_options_raw &= ~PRINT_OPTION; // Unset flag
                    }

                    modified = true;
                }
            }
        }
        ImGui::EndGroup();

        return modified;
    };

    // -------------------------------------------------------------------------

    int print_options_raw = print_options;

    const bool modified = YGPrintOptions_checkboxes_raw(print_options_raw);

    if(modified)
    {
        // Assign raw value into enum
        print_options = static_cast<YGPrintOptions>(print_options_raw);
    }

    return modified;
}

void ImGui_Yoga::YGPrintOptions_text(const YGPrintOptions& print_options)
{
    const bool is__option_layout__enabled   = (print_options & YGPrintOptions::YGPrintOptionsLayout)   != 0;
    const bool is__option_style__enabled    = (print_options & YGPrintOptions::YGPrintOptionsStyle)    != 0;
    const bool is__option_children__enabled = (print_options & YGPrintOptions::YGPrintOptionsChildren) != 0;

    const bool is_all_enabled  = ( is__option_layout__enabled &&  is__option_style__enabled &&  is__option_children__enabled);
    const bool is_none_enabled = (!is__option_layout__enabled && !is__option_style__enabled && !is__option_children__enabled);

    if(is_all_enabled)
    {
        ImGui::TextUnformatted("all");
    }
    else // Not all enabled --> 'none' or 'some'
    {
        if(is_none_enabled)
        {
            ImGui::TextUnformatted("none");
        }
        else // 'some' enabled
        {
            ImGui::Text(
                "%s:%s %s:%s %s:%s",

                YGPrintOptionsToString(YGPrintOptions::YGPrintOptionsLayout),
                (is__option_layout__enabled   ? "true" : "false"),

                YGPrintOptionsToString(YGPrintOptions::YGPrintOptionsStyle),
                (is__option_style__enabled    ? "true" : "false"),

                YGPrintOptionsToString(YGPrintOptions::YGPrintOptionsChildren),
                (is__option_children__enabled ? "true" : "false")
            );
        }
    }
}

bool ImGui_Yoga::YGUnit_combo(const char* label, YGUnit& unit)
{
    constexpr YGUnit UNITS[]
    {
        YGUnit::YGUnitUndefined,
        YGUnit::YGUnitPoint,
        YGUnit::YGUnitPercent,
        YGUnit::YGUnitAuto
    };

    bool modified = false;

    const char* combo_label = YGUnitToString(unit);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGUnit unit_to_choose : UNITS)
        {
            const bool is_selected = (unit_to_choose == unit);

            const char* selectable_label = YGUnitToString(unit_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                unit = unit_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGWrap_combo(const char* label, YGWrap& wrap)
{
    constexpr YGWrap WRAPS[]
    {
        YGWrap::YGWrapNoWrap,
        YGWrap::YGWrapWrap,
        YGWrap::YGWrapWrapReverse
    };

    bool modified = false;

    const char* combo_label = YGWrapToString(wrap);

    if (ImGui::BeginCombo(label, combo_label))
    {
        for (const YGWrap wrap_to_choose : WRAPS)
        {
            const bool is_selected = (wrap_to_choose == wrap);

            const char* selectable_label = YGWrapToString(wrap_to_choose);
            if (ImGui::Selectable(selectable_label, is_selected))
            {
                wrap = wrap_to_choose;

                modified = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    return modified;
}

bool ImGui_Yoga::YGWrap_radio(YGWrap& wrap)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        {
            constexpr YGWrap WRAP = YGWrap::YGWrapNoWrap;
            if( ImGui::RadioButton( YGWrapToString(WRAP), (wrap == WRAP)) )
            {
                wrap = WRAP;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGWrap WRAP = YGWrap::YGWrapWrap;
            if( ImGui::RadioButton( YGWrapToString(WRAP), (wrap == WRAP)) )
            {
                wrap = WRAP;
                modified = true;
            }
        }

        ImGui::SameLine();

        {
            constexpr YGWrap WRAP = YGWrap::YGWrapWrapReverse;
            if( ImGui::RadioButton( YGWrapToString(WRAP), (wrap == WRAP)) )
            {
                wrap = WRAP;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    return modified;
}

