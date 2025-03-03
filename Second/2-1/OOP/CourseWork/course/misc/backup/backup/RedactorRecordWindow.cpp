#include "RedactorRecordWindow.h"
#include "ui_RedactorRecordWindow.h"

// Инициализация и открытие окна
RedactorRecordWindow::RedactorRecordWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RedactorRecordWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    setWindowTitle(" ");
}

// Деструктор
RedactorRecordWindow::~RedactorRecordWindow()
{
    delete ui;
}

// Все методы для установки значений полей окна, принимающие QString
void RedactorRecordWindow::setName(const QString& lineValue) {
    ui->lineEdit->setText(lineValue);
}

void RedactorRecordWindow::setSeatCount(const QString& value) {
    ui->lineEdit_2->setText(value);
}

void RedactorRecordWindow::setAvailableSeats(const QString& value) {
    ui->lineEdit_3->setText(value);
}

void RedactorRecordWindow::setManufactureYear(const QString& value) {
    ui->lineEdit_4->setText(value);
}

// Метод getData для извлечения данных из полей
RailwayCarriage RedactorRecordWindow::getData() {
    RailwayCarriage resultRecord;
    resultRecord.setName(ui->lineEdit->text().simplified());  // Название вагона
    resultRecord.setSeatCount(ui->lineEdit_2->text().simplified());  // Количество мест
    resultRecord.setAvailableSeats(ui->lineEdit_3->text().simplified());  // Свободные места
    resultRecord.setManufactureYear(ui->lineEdit_4->text().simplified());  // Год выпуска
    return resultRecord;
}
