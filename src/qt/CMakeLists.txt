FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Widgets Core Sql)
qt_standard_project_setup()

ADD_SUBDIRECTORY(app)
ADD_SUBDIRECTORY(businesslogic)