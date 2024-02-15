#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void slotAddTodo();
    void slotRemoveTodo();

  private:
    Ui::MainWindow *ui;
    QStringList *list;
    QStringListModel *model;
};

#endif// MAINWINDOW_H