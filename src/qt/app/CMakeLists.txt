qt_add_executable(qt-helloworld
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

target_link_libraries(qt-helloworld PRIVATE 
    businesslogic
    Qt6::Widgets
    Qt6::Sql)

set_target_properties(qt-helloworld PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)