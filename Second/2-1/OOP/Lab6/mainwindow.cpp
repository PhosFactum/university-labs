#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Добавляем placeholder text для LineEdit
    ui->lineEditLeft->setPlaceholderText("Type the L-line");
    ui->lineEditRight->setPlaceholderText("Type the R-line");
    ui->lineEditResult->setPlaceholderText("Here is a result line");

    // Соединяем кнопки с соответствующими обработчиками
    connect(ui->btnReverseLeft, &QPushButton::clicked, this, &MainWindow::onReverseLeftClicked);
    connect(ui->btnReverseRight, &QPushButton::clicked, this, &MainWindow::onReverseRightClicked);
    connect(ui->btnReverseAll, &QPushButton::clicked, this, &MainWindow::onReverseAllClicked);
    connect(ui->btnSwap, &QPushButton::clicked, this, &MainWindow::onSwapClicked);
    connect(ui->btnConcatLeft, &QPushButton::clicked, this, &MainWindow::onConcatLeftClicked);
    connect(ui->btnConcatRight, &QPushButton::clicked, this, &MainWindow::onConcatRightClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Реализация обработчиков
void MainWindow::onReverseLeftClicked()
{
    QString text = ui->lineEditLeft->text();
    std::reverse(text.begin(), text.end());
    ui->lineEditResult->setText(text);
}

void MainWindow::onReverseRightClicked()
{
    QString text = ui->lineEditRight->text();
    std::reverse(text.begin(), text.end());
    ui->lineEditResult->setText(text);
}

void MainWindow::onReverseAllClicked()
{
    QString leftText = ui->lineEditLeft->text();
    QString rightText = ui->lineEditRight->text();

    std::reverse(leftText.begin(), leftText.end());
    std::reverse(rightText.begin(), rightText.end());

    ui->lineEditResult->setText(leftText + " | " + rightText);
}

void MainWindow::onSwapClicked()
{
    QString leftText = ui->lineEditLeft->text();
    QString rightText = ui->lineEditRight->text();

    ui->lineEditLeft->setText(rightText);
    ui->lineEditRight->setText(leftText);
}

void MainWindow::onConcatLeftClicked()
{
    QString result = ui->lineEditLeft->text() + ui->lineEditRight->text();
    ui->lineEditResult->setText(result);
}

void MainWindow::onConcatRightClicked()
{
    QString result = ui->lineEditRight->text() + ui->lineEditLeft->text();
    ui->lineEditResult->setText(result);
}
