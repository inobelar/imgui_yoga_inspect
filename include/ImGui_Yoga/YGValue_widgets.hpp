#ifndef IMGUI_YOGA__YGVALUE_WIDGETS_HPP
#define IMGUI_YOGA__YGVALUE_WIDGETS_HPP

#include <yoga/Yoga.h>

namespace ImGui_Yoga {

bool YGValue_edit(const char* label, YGValue& value);

void YGValue_text(const YGValue& value);

void YGValue_text_disabled(const YGValue& value);

} // namespace ImGui_Yoga

#endif // IMGUI_YOGA__YGVALUE_WIDGETS_HPP
