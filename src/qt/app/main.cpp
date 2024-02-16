
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

const char *TABLE_NAME = "task";

const auto TASK_SQL = QLatin1String(R"(
    create table task(id integer primary key, name varchar)
    )");

const auto INSERT_TASK_SQL = QLatin1String(R"(
    insert into task(name) values(?)
    )");

// expected only from c++23
QSqlDatabase createDB()
{
    QDir databasePath{};
    QString path = databasePath.currentPath() + "/myDb.db";// Not "myDb.db"
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) { throw(std::ios_base::failure("Database opening failed!")); }

    QStringList tables = db.tables();
    if (!tables.contains(TABLE_NAME, Qt::CaseInsensitive)) {
        QSqlQuery q;
        if (!q.exec(TASK_SQL)) {
            throw(std::ios_base::failure(
              "Database opening failed!" + q.lastError().text().toStdString()));
        }
    }


    // TODO prepare

    return std::move(db);
}

QSqlTableModel *createModel(const QSqlDatabase &db)
{
    QSqlTableModel *model = new QSqlTableModel(nullptr, db);

    model->setTable(TABLE_NAME);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);


    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, QObject::tr("Name"));

    if (!model->select()) {
        throw(std::ios_base::failure(
          "Model select failed!" + model->lastError().text().toStdString()));
    }

    return model;
}

void addTask(const QString &name)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_TASK_SQL)) {
        throw(std::ios_base::failure(
          "Query preapre failed!" + q.lastError().text().toStdString()));
    }
    q.addBindValue(name);
    q.exec();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        throw(std::ios_base::failure("QSQLITE Driver not found!"));
    }

    const QSqlDatabase db = createDB();
    QSqlTableModel *model = createModel(db);

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

    MainWindow mainW(nullptr, model);
    mainW.show();
    mainW.setWindowTitle("Todo Application");

    return app.exec();
}
