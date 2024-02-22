FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# sets CMAKE_AUTOMOC and CMAKE_AUTOUIC to true
qt_standard_project_setup()

qt_add_executable(wiki 
    wiki-ex.cpp
    my_widget.hpp
)


target_link_libraries(wiki
    PRIVATE
        Qt6::Gui
        Qt6::Core
        Qt6::Widgets
)

set_target_properties(wiki PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)