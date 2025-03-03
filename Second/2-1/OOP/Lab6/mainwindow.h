#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onReverseLeftClicked();
    void onReverseRightClicked();
    void onReverseAllClicked();
    void onSwapClicked();
    void onConcatLeftClicked();
    void onConcatRightClicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

