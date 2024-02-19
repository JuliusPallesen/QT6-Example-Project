FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Widgets Core Sql)

# sets CMAKE_AUTOMOC and CMAKE_AUTOUIC to true
# see https://doc.qt.io/qt-6/qt-standard-project-setup.html
qt_standard_project_setup()

ADD_SUBDIRECTORY(app)
ADD_SUBDIRECTORY(businesslogic)