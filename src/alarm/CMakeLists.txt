FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

qt_standard_project_setup()

qt_add_executable(alarm
    main.cpp
    alarm.hpp
    AlarmsListModel.hpp
)

qt_add_qml_module(
    alarm
    URI
        QtExampleProject
    QML_FILES
        alarm.qml
        AlarmListView.qml
)

target_link_libraries(alarm
    PRIVATE
        Qt6::Gui
        Qt6::Core
        Qt6::Quick
)

set_target_properties(alarm PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)