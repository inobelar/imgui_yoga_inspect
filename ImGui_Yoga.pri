# QMake project include file
#
# Example of usage
#
# Add into your *.pro project file the next line:
#
#   include(/path/to/imgui_yoga_inspect/ImGui_Yoga.pri)
#
# NOTE: content is based on ImGui_Yoga.cmake

INCLUDEPATH += \
    $$PWD/include/
    
HEADERS += \
    $$PWD/include/ImGui_Yoga/enums.hpp \
    $$PWD/include/ImGui_Yoga/utility_widgets.hpp \
    $$PWD/include/ImGui_Yoga/YGNode_draw_recursive.hpp \
    \
    $$PWD/include/ImGui_Yoga/YGNode_inspect_full.hpp \
    $$PWD/include/ImGui_Yoga/YGNode_inspect_web.hpp \
    \
    $$PWD/include/ImGui_Yoga/YGNode_reflect_full.hpp \
    $$PWD/include/ImGui_Yoga/YGNode_reflect_web.hpp \
    \
    $$PWD/include/ImGui_Yoga/YGValue_widgets.hpp
    
SOURCES += \
    $$PWD/sources/imgui_yoga__enums.cpp \
    $$PWD/sources/imgui_yoga__utility_widgets.cpp \
    $$PWD/sources/imgui_yoga__YGNode_draw_recursive.cpp \
    \
    $$PWD/sources/imgui_yoga__YGNode_inspect_full.cpp \
    $$PWD/sources/imgui_yoga__YGNode_inspect_web.cpp \
    \
    $$PWD/sources/imgui_yoga__YGNode_reflect_full.cpp \
    $$PWD/sources/imgui_yoga__YGNode_reflect_web.cpp \
    \
    $$PWD/sources/imgui_yoga__YGValue_widgets.cpp
