#include <ImGui_Yoga/utility_widgets.hpp>

#include <imgui.h>

/*
    Helper to display a little (?) mark which shows a tooltip when hovered.

    Directly copied from `imgui_demo.cpp`
*/
void ImGui_Yoga::HelpMarker(const char* description)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        if (ImGui::BeginTooltip())
        {
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            {
                ImGui::TextUnformatted(description);
            }
            ImGui::PopTextWrapPos();

            ImGui::EndTooltip();
        }
    }
}
