#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QDir>
#include <QMessageBox>
#include <QShortcut>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <iostream>

const char *TABLE_NAME = "task";
const char *TABLE_TASK_NAME = "name";

const auto TASK_SQL = QLatin1String(R"(
    create table task(id integer primary key, name varchar)
    )");

const auto INSERT_TASK_SQL = QLatin1String(R"(
    insert into task(name) values(?)
    )");


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::MainWindow), model{ nullptr }
{
    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        throw(std::ios_base::failure("QSQLITE Driver not found!"));
    }

    const QSqlDatabase db = createDB();
    model = createModel(db);

    ui->pushButton->setText("Commit");

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(
      QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnHidden(model->fieldIndex("id"), true);

    connect(ui->pushButton, SIGNAL(released()), this, SLOT(slotAddTodo()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(slotAddTodo()));

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->tableView);
    connect(shortcut, SIGNAL(activated()), this, SLOT(slotRemoveTodo()));

    createMenuBar();
}

MainWindow::~MainWindow() { delete ui; }

QSqlRecord MainWindow::createEntry(QString name)
{
    QSqlRecord record = model->record();
    record.setValue(model->fieldIndex(TABLE_TASK_NAME), name);
    return record;
}


void MainWindow::slotAddTodo()
{
    QString addedStr = ui->lineEdit->text();
    if (!addedStr.isEmpty()) {

        // Append string to model
        int count = model->rowCount();
        model->insertRows(count, 1);
        // QModelIndex index = model->index(count, 1);//
        // model->setData(index, createEntry(addedStr))
        QSqlRecord record = model->record(count);
        record.setValue(TABLE_TASK_NAME, addedStr);
        model->setRecord(count, record);
        model->submitAll();
        // Impl is very coupled to sql usage - rethink

        // Clear LineEdit Field
        ui->lineEdit->setText("");
    }
}

void MainWindow::slotRemoveTodo()
{
    QModelIndex listIndex = ui->tableView->currentIndex();
    if (model->rowCount() > 0) {
        model->removeRows(listIndex.row(), 1);
        model->submitAll();
    }
}

void MainWindow::createMenuBar()
{
    QAction *quitAction = new QAction(tr("&Quit"), this);
    QAction *aboutAction = new QAction(tr("&About"), this);
    QAction *aboutQtAction = new QAction(tr("&About Qt"), this);
    QAction *syncAction = new QAction(tr("&Sync"), this);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    menuBar()->addAction(syncAction);

    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(syncAction, SIGNAL(triggered()), this->model, SLOT(submitAll()));
}

void MainWindow::about()
{
    QMessageBox::about(this,
      tr("About Todo App"),
      tr("<p>The <b>Todo App</b> example shows how to use QT Widgets and Qt SQL "
         "classes "));
}


// expected only from c++23
QSqlDatabase MainWindow::createDB()
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

    return std::move(db);
}

QSqlTableModel *MainWindow::createModel(const QSqlDatabase &db)
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

void MainWindow::addTask(const QString &name)
{
    QSqlQuery q;
    if (!q.prepare(INSERT_TASK_SQL)) {
        throw(std::ios_base::failure(
          "Query prepare failed!" + q.lastError().text().toStdString()));
    }
    q.addBindValue(name);
    q.exec();
}
