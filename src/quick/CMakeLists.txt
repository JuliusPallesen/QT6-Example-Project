FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

qt_standard_project_setup()

qt_add_executable(playground
    playground.cpp
    invokable.hpp
)

qt_add_qml_module(
    playground
    URI
        QtExampleProject
    QML_FILES
        helloworld.qml
        HelloWorldText.qml
    RESOURCES
        zühlke_logo.png
)

target_link_libraries(playground
    PRIVATE
        Qt6::Gui
        Qt6::Core
        Qt6::Quick
)

set_target_properties(playground PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)