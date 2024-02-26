FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Quick Gui)

qt_standard_project_setup()

qt_add_executable(navalfate
    main.cpp
)

qt_add_qml_module(
    navalfate
    URI
        QtExampleProject
    QML_FILES
        main.qml
)

ADD_LIBRARY(entities entity.h entity.cpp mine.h mine.cpp ship.h ship.cpp)
ADD_LIBRARY(battlefield battlefield.hpp battlefield.cpp)

target_link_libraries(navalfate
    PRIVATE
        Qt6::Gui
        Qt6::Core
        Qt6::Quick
        entities
        battlefield
)

set_target_properties(navalfate PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)