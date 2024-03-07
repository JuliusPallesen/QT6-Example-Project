FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

qt_standard_project_setup()

qt_add_executable(alarm
    main.cpp
    backend/alarm.hpp
    backend/AlarmsListModel.hpp
    backend/TimerBackend.hpp
)

qt_add_qml_module(
    alarm
    URI
        QtExampleProject
    QML_FILES
        view/alarm.qml
        view/AlarmListView.qml
        view/AlarmRinging.qml
        view/EditAlarm.qml
    RESOURCES
	resource/clock_black.png
	resource/clock_white.png
	resource/repeating_black.png
	resource/repeating_grey.png
	resource/repeating_white.png
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