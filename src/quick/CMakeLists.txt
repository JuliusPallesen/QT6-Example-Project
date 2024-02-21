FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

# sets CMAKE_AUTOMOC and CMAKE_AUTOUIC to true
qt_standard_project_setup()

qt_add_executable(playground
    playground.cpp
)

qt_add_qml_module(
    playground
    URI
        QtExampleProject
    QML_FILES
        helloworld.qml
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