#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Vector.h"
#include "RailwayCarriage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_New_triggered();

    void on_action_About_triggered();

    void on_action_Exit_triggered();

    void on_action_Add_triggered();

    void on_lineEdit_textChanged(const QString &textToSearch);

    void on_action_Edit_triggered();

    void on_action_Delete_triggered();

    void on_action_Clear_triggered();

    void on_action_Open_triggered(bool isCleanCurrentTable = true);

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Merge_triggered();

    void on_tableWidget_cellDoubleClicked(int, int);

    void on_action_ShowData_triggered();

    void createNewDatabase();

private:
    Ui::MainWindow *ui;
    QString file_ = "";
    Vector<RailwayCarriage> main_vector;
};

#endif // MAINWINDOW_H
