#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0, QSqlTableModel *viewModel = nullptr);
    ~MainWindow();

  private:
    void createMenuBar();
    void about();

  private slots:
    void slotAddTodo();
    void slotRemoveTodo();

  private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
};

#endif// MAINWINDOW_H