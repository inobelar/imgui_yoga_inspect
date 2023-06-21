#[[
    CMake project include file

    # Example of usage

    Add into your CMakeLists.txt the next lines:

    # --------------------------------------------------------------------------

    # Add 'ImGui_Yoga' into modules search path - to find this file (ImGui_Yoga.cmake)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/path/to/imgui_yoga_inspect/")
    include(ImGui_Yoga)

    add_executable( <YOUR_EXECUTABLE>
        # ...
        ${IMGUI_YOGA_HEADERS} ${IMGUI_YOGA_SOURCES}
    )

    # Add 'ImGui_Yoga' includes search path
    target_include_directories( <YOUR_EXECUTABLE> ${IMGUI_YOGA_INCLUDE_DIRECTORIES} )

    # (Example) Add 'ImGui_Yoga' dependency libraries (ImGui and Yoga libraries)
    target_link_libraries( <YOUR_EXECUTABLE> imgui yoga )

    # --------------------------------------------------------------------------
]]

set(IMGUI_YOGA_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

set(IMGUI_YOGA_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/enums.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/utility_widgets.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/YGNode_draw_recursive.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/YGNode_inspect_full.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/YGNode_inspect_web.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/YGNode_reflect_full.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/YGNode_reflect_web.hpp

    ${CMAKE_CURRENT_LIST_DIR}/include/ImGui_Yoga/YGValue_widgets.hpp
)

set(IMGUI_YOGA_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__enums.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__utility_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__YGNode_draw_recursive.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__YGNode_inspect_full.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__YGNode_inspect_web.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__YGNode_reflect_full.cpp
    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__YGNode_reflect_web.cpp

    ${CMAKE_CURRENT_LIST_DIR}/sources/imgui_yoga__YGValue_widgets.cpp
)
