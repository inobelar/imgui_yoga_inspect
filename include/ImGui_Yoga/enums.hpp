#ifndef IMGUI_YOGA__ENUMS_HPP
#define IMGUI_YOGA__ENUMS_HPP

#include <yoga/Yoga.h>

namespace ImGui_Yoga {

/*
    Note:

    - in the next functions used reference to modified value, instead of
      pointer (such design is used in most ImGui widgets), since nullptr is
      not acceptable.

    - for enumerations with relatively small count provided various forms:
      combo-boxes and radio-buttons.
*/

bool YGAlign_combo(const char* label, YGAlign& align);


bool YGDimension_combo(const char* label, YGDimension& dimention);

bool YGDimension_radio(YGDimension& dimension);


bool YGDirection_combo(const char* label, YGDirection& direction);

bool YGDirection_radio(YGDirection& direction);


bool YGDisplay_combo(const char* label, YGDisplay& display);

bool YGDisplay_radio(YGDisplay& display);


bool YGEdge_combo(const char* label, YGEdge& edge);


// TODO: YGExperimentalFeature enum


bool YGFlexDirection_combo(const char* label, YGFlexDirection& flex_direction);


bool YGGutter_combo(const char* label, YGGutter& gutter);

bool YGGutter_radio(YGGutter& gutter);


bool YGJustify_combo(const char* label, YGJustify& justification);


bool YGLogLevel_combo(const char* label, YGLogLevel& log_level);


bool YGMeasureMode_combo(const char* label, YGMeasureMode& measure_mode);

bool YGMeasureMode_radio(YGMeasureMode& measure_mode);


bool YGNodeType_combo(const char* label, YGNodeType& node_type);

bool YGNodeType_radio(YGNodeType& node_type);


bool YGOverflow_combo(const char* label, YGOverflow& overflow);

bool YGOverflow_radio(YGOverflow& overflow);


bool YGPositionType_combo(const char* label, YGPositionType& pos_type);

bool YGPositionType_radio(YGPositionType& pos_type);


bool YGPrintOptions_combo(const char* label, YGPrintOptions& print_options);

bool YGPrintOptions_checkboxes(YGPrintOptions& print_options);

void YGPrintOptions_text(const YGPrintOptions& print_options);


bool YGUnit_combo(const char* label, YGUnit& unit);


bool YGWrap_combo(const char* label, YGWrap& wrap);

bool YGWrap_radio(YGWrap& wrap);

} // namespace ImGui_Yoga

#endif // IMGUI_YOGA__ENUMS_HPP

