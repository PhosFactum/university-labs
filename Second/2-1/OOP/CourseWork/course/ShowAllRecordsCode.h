#ifndef SHOWALLRECORDSCODE_H
#define SHOWALLRECORDSCODE_H

#include <QDialog>

namespace Ui {
class ShowAllRecordsCode;
}

class ShowAllRecordsCode : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAllRecordsCode(QWidget *parent = nullptr);

    void setText(const QString &str);

    QString getText();

    ~ShowAllRecordsCode();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ShowAllRecordsCode *ui;
};

#endif // SHOWALLRECORDSCODE_H
