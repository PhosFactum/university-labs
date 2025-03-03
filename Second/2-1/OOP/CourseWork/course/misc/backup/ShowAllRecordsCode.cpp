#include "ShowAllRecordsCode.h"
#include "ui_ShowAllRecordsCode.h"


//Инициализация и открытие окна
ShowAllRecordsCode::ShowAllRecordsCode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAllRecordsCode)
{
    ui->setupUi(this);
}

//Метод записи данных в поле окна
void ShowAllRecordsCode::setText(const QString &str) {
    ui->textEdit->setText(str);
}

//Метод считывания данных из поля окна
QString ShowAllRecordsCode::getText() {
    return ui->textEdit->toPlainText();
}

//Деструктор
ShowAllRecordsCode::~ShowAllRecordsCode()
{
    delete ui;
}

//При нажатии кнопки "Close" окно закрывается
void ShowAllRecordsCode::on_pushButton_clicked()
{
    this->close();
}
