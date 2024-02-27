FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

qt_standard_project_setup()

qt_add_executable(mvex
    main.cpp
    tiles.h
)

qt_add_qml_module(
    mvex
    URI
        QtExampleProject
    QML_FILES
        main.qml
    RESOURCES
        mine.png
        ship.png
        water.png
)

target_link_libraries(mvex
    PRIVATE
        Qt6::Gui
        Qt6::Core
        Qt6::Quick
)

set_target_properties(mvex PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)