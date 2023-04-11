#include <ImGui_Yoga/YGValue_widgets.hpp>

#include <imgui.h>

#include <ImGui_Yoga/enums.hpp>

#include <string>

// FIXME: ImGui::SetNextItemWidth(100); somehow beautiful

bool ImGui_Yoga::YGValue_edit(const char* label, YGValue& value)
{
    bool modified = false;

    ImGui::BeginGroup();
    {
        // 'value' modifying
        switch (value.unit) {
        case YGUnit::YGUnitUndefined:
        {
            // No 'value' edit
        } break;
        case YGUnit::YGUnitPoint:
        {
            const std::string drag_label = std::string(label) + "_point";

            ImGui::SetNextItemWidth(100);

            float point_value = value.value;
            if( ImGui::DragFloat(drag_label.c_str(), &point_value) )
            {
                value.value = point_value;
                modified = true;
            }

            ImGui::SameLine();
        } break;
        case YGUnit::YGUnitPercent:
        {
            const std::string drag_label = std::string(label) + "_percent";

            ImGui::SetNextItemWidth(100);

            float percent_value = value.value;
            if( ImGui::DragFloat(drag_label.c_str(), &percent_value, 1.0f, 0.0f, 100.0f) )
            {
                value.value = percent_value;
                modified = true;
            }

            ImGui::SameLine();
        } break;
        case YGUnit::YGUnitAuto:
        {
            // No 'value' edit
        } break;
        }

        // 'unit' modifying
        {
            const std::string unit_label = std::string(label) + "_unit";

            ImGui::SetNextItemWidth(100);

            YGUnit unit = value.unit;
            if( YGUnit_combo(unit_label.c_str(), unit) )
            {
                // In case of 'point' or 'percent' - if value is undefined - set it to 0.0.
                switch (unit) {
                case YGUnit::YGUnitUndefined: {
                    // Dont try to change 'value'
                } break;
                case YGUnit::YGUnitPoint: {
                    if( YGFloatIsUndefined(value.value) )
                        value.value = 0.0f;
                } break;
                case YGUnit::YGUnitPercent: {
                    if( YGFloatIsUndefined(value.value) )
                        value.value = 0.0f;
                } break;
                case YGUnit::YGUnitAuto: {
                    // Dont try to change 'value'
                } break;
                }

                value.unit = unit;
                modified = true;
            }
        }
    }
    ImGui::EndGroup();

    // Show tooltip with raw data
    if ( ImGui::IsItemHovered() )
    {
        ImGui::SetTooltip(
            "value: %f\nunit: %s",
            value.value, YGUnitToString(value.unit)
        );
    }

    return modified;
}

void ImGui_Yoga::YGValue_text(const YGValue& value)
{
    switch (value.unit) {
    case YGUnit::YGUnitUndefined:
    {
        ImGui::TextUnformatted( YGUnitToString(value.unit) );
    } break;
    case YGUnit::YGUnitPoint:
    {
        ImGui::Text("%f (%s)", value.value, YGUnitToString(value.unit) );
    } break;
    case YGUnit::YGUnitPercent:
    {
        ImGui::Text("%f (%s)", value.value, YGUnitToString(value.unit) );
    } break;
    case YGUnit::YGUnitAuto:
    {
        ImGui::TextUnformatted( YGUnitToString(value.unit) );
    } break;
    }

    // Show tooltip with raw data
    if ( ImGui::IsItemHovered() )
    {
        ImGui::SetTooltip(
            "value: %f\nunit: %s",
            value.value, YGUnitToString(value.unit)
        );
    }
}

void ImGui_Yoga::YGValue_text_disabled(const YGValue& value)
{
    switch (value.unit) {
    case YGUnit::YGUnitUndefined:
    {
        ImGui::TextDisabled("%s", YGUnitToString(value.unit) );
    } break;
    case YGUnit::YGUnitPoint:
    {
        ImGui::TextDisabled("%f (%s)", value.value, YGUnitToString(value.unit) );
    } break;
    case YGUnit::YGUnitPercent:
    {
        ImGui::TextDisabled("%f (%s)", value.value, YGUnitToString(value.unit) );
    } break;
    case YGUnit::YGUnitAuto:
    {
        ImGui::TextDisabled("%s", YGUnitToString(value.unit) );
    } break;
    }

    // Show tooltip with raw data
    if ( ImGui::IsItemHovered() )
    {
        ImGui::SetTooltip(
            "value: %f\nunit: %s",
            value.value, YGUnitToString(value.unit)
        );
    }
}
