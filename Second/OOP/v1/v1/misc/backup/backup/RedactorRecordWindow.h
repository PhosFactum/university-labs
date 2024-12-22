#ifndef RedactorRecordWindow_H
#define RedactorRecordWindow_H

#include <QDialog>
#include "RailwayCarriage.h"

namespace Ui {
class RedactorRecordWindow;
}

class RedactorRecordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RedactorRecordWindow(QWidget *parent = nullptr);

    void setName(const QString& lineValue);
    void setSeatCount(const QString& value);
    void setAvailableSeats(const QString& value);
    void setManufactureYear(const QString& value);

    RailwayCarriage getData();

    ~RedactorRecordWindow();

private:
    Ui::RedactorRecordWindow *ui;
};

#endif // RedactorRecordWindow_H
