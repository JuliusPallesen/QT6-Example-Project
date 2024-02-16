
#include "mainwindow.h"
#include <QApplication>

#include <QDir>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <ios>
#include <iostream>

#include <QtSql>

#include <QSqlError>
#include <QSqlQuery>
#include <expected>

// TODO adhere to QSqlError usage and not exception throwing


int main(int argc, char **argv)
{
    QApplication app(argc, argv);


    // QSqlRecord tempRecord{};
    // tempRecord.setValue("id", "0");
    // tempRecord.setValue("name", "Do stuff");

    // if (!model->insertRecord(-1, tempRecord)) {
    // throw(std::ios_base::failure("Model select failed!" +
    // model->lastError().text().toStdString())); } addTask("Working");

    // model->submitAll();

    // QSqlRecord retRecord = model->record(0);
    // std::cout << "Name: " << retRecord.fieldName(0).toStdString() << ",
    // Value: " << retRecord.value(0).toString().toStdString() << std::endl;
    //  QAbstractItemModel *model = new QStringListModel(nullptr);

    // TODO Try to manipulate manually first

    MainWindow mainW{};
    mainW.show();
    mainW.setWindowTitle("Todo Application");

    return app.exec();
}
