FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

# sets CMAKE_AUTOMOC and CMAKE_AUTOUIC to true
qt_standard_project_setup()

qt_add_executable(helloworld
    helloworld.cpp
)

qt_add_qml_module(
    helloworld
    URI
        myqtwidgetsproject
    QML_FILES
        helloworld.qml
)

target_link_libraries(helloworld
    PRIVATE
        Qt6::Gui
        Qt6::Core
        Qt6::Quick
)

set_target_properties(helloworld PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)