#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RedactorRecordWindow.h"
#include "ShowAllRecordsCode.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include "Vector.h"
#include "TextMessageDictionary.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(NAME_OF_OBJECT_TYPE); // Установка заголовка окна приложения
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Метод добавления записи
void MainWindow::on_action_Add_triggered()
{
    RedactorRecordWindow addRecordDialogWindow;
    if (addRecordDialogWindow.exec() == QDialog::Accepted)
    {
        RailwayCarriage newRecord = addRecordDialogWindow.getData();

        main_vector.push_back(newRecord);

        int newRowIndex = ui->tableWidget->rowCount();

        ui->tableWidget->setRowCount(newRowIndex + 1);
        ui->tableWidget->setItem(newRowIndex, 0, new QTableWidgetItem(QString::number(newRowIndex + 1)));
        ui->tableWidget->setItem(newRowIndex, 1, new QTableWidgetItem(newRecord.getName()));
        ui->tableWidget->setItem(newRowIndex, 2, new QTableWidgetItem(newRecord.getSeatCount())); // getSeatCount() уже возвращает QString
        ui->tableWidget->setItem(newRowIndex, 3, new QTableWidgetItem(newRecord.getAvailableSeats()));
        ui->tableWidget->setItem(newRowIndex, 4, new QTableWidgetItem(newRecord.getManufactureYear()));

        ui->statusBar->showMessage(OBJECT_ADD_MESSAGE);
        setWindowTitle(WINDOW_TITLE_UNSAVED_SYMBOL + file_ + WINDOW_TITLE_TYPE_OBJECT);
    }
}


//МЕТОД РЕДАКТИРОВАНИЯ ЗАПИСИ
void MainWindow::on_action_Edit_triggered()
{
    auto selectedItemsList = ui->tableWidget->selectedItems();
    if (selectedItemsList.size() == 0) {
        return;
    }

    RedactorRecordWindow editRecordDialogWindow;
    editRecordDialogWindow.setName(selectedItemsList.at(1)->text());
    editRecordDialogWindow.setSeatCount(QString::number(selectedItemsList.at(2)->text().toInt()));
    editRecordDialogWindow.setAvailableSeats(QString::number(selectedItemsList.at(3)->text().toInt()));
    editRecordDialogWindow.setManufactureYear(QString::number(selectedItemsList.at(4)->text().toInt()));


    if (editRecordDialogWindow.exec() == QDialog::Accepted) {
        RailwayCarriage editedRecord = editRecordDialogWindow.getData();

        main_vector[selectedItemsList.at(1)->row()].setName(editedRecord.getName());
        main_vector[selectedItemsList.at(2)->row()].setSeatCount(editedRecord.getSeatCount());
        main_vector[selectedItemsList.at(3)->row()].setAvailableSeats(editedRecord.getAvailableSeats());
        main_vector[selectedItemsList.at(4)->row()].setManufactureYear(editedRecord.getManufactureYear());

        selectedItemsList.at(1)->setText(editedRecord.getName());
        selectedItemsList.at(2)->setText(editedRecord.getSeatCount());
        selectedItemsList.at(3)->setText(editedRecord.getAvailableSeats());
        selectedItemsList.at(4)->setText(editedRecord.getManufactureYear());

        ui->statusBar->showMessage(OBJECT_REDACT_MESSAGE);
        setWindowTitle(WINDOW_TITLE_UNSAVED_SYMBOL + file_ + WINDOW_TITLE_TYPE_OBJECT);
    }
}

//МЕТОД СОЗДАНИЯ НОВОГО ФАЙЛА
void MainWindow::on_action_New_triggered()
{
    if (ui->tableWidget->rowCount() == 0) {
        MainWindow::createNewDatabase();
        return;
    }

    QMessageBox msgBox;

    msgBox.setWindowTitle(ATTENTION_MESSAGE);
    msgBox.setText(WARNING_WHEN_CREATING_NEW_FILE);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    if (msgBox.exec() == QMessageBox::No) {
        return;
    }

    MainWindow::createNewDatabase();
}

//МЕТОД ЗАКРЫТИЯ ПРИЛОЖЕНИЯ
void MainWindow::on_action_Exit_triggered()
{
    if (ui->tableWidget->rowCount() == 0 && file_ == "") {
        exit(0);
    }

    QMessageBox msgBox;

    msgBox.setWindowTitle(ATTENTION_MESSAGE);
    msgBox.setText(WARNING_WHEN_CLOSE_APPLICATION);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    if (msgBox.exec() == QMessageBox::No) {
        return;
    }

    exit(0);
}

//МЕТОД ОПИСАНИЯ КУРСОВОЙ РАБОТЫ
void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,
                       ABOUT_COURSE_WORK_MESSAGE_TITLE,
                       ABOUT_COURSE_WORK_MESSAGE_NAME
                           ABOUT_COURSE_WORK_MESSAGE_THEME
                               ABOUT_COURSE_WORK_MESSAGE_VERSION
                                   ABOUT_COURSE_WORK_MESSAGE_GROUP
                                       ABOUT_COURSE_WORK_MESSAGE_FULL_NAME
                                           ABOUT_COURSE_WORK_MESSAGE_CITY
                                               ABOUT_COURSE_WORK_MESSAGE_YEAR);
}

//МЕТОД ПОИСКОВОЙ СТРОКИ
void MainWindow::on_lineEdit_textChanged(const QString &textToSearch)
{
    ui->tableWidget->setCurrentCell(-1, -1);

    if (textToSearch == "") {
        ui->statusBar->showMessage("");
        return;
    }

    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);

    auto find_items = ui->tableWidget->findItems(textToSearch, Qt::MatchContains);

    int len = find_items.size();
    for (int i = 0; i < len; ++i) {
        auto item = find_items.at(i);
        item->setSelected(true);
    }

    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->statusBar->showMessage(RESULT_SEARCH_MESSAGE_FIRST_PART + QString::number(len) + RESULT_SEARCH_MESSAGE_SECOND_PART);
}

//МЕТОД УДАЛЕНИЯ ВЫДЕЛЕННЫХ ЗАПИСЕЙ В ТАБЛИЦЕ
void MainWindow::on_action_Delete_triggered()
{
    auto selectRecordsList = ui->tableWidget->selectionModel()->selectedRows();

    if (selectRecordsList.size() == 0) {
        ui->statusBar->showMessage(NO_OBJECTS_MESSAGE);
        return;
    }

    std::sort(selectRecordsList.begin(), selectRecordsList.end(), [](const QModelIndex &a, const QModelIndex &b) {
        return a.row() < b.row();
    });

    QMessageBox messageBox;

    messageBox.setWindowTitle(ATTENTION_MESSAGE);
    messageBox.setText(WARNING_WHEN_DELETED_SELECTED_LINES);
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);

    if (messageBox.exec() == QMessageBox::No) {
        return;
    }

    int indexOffset = 0;

    for (auto selectedListIndex = 0; selectedListIndex < selectRecordsList.size(); selectedListIndex++) {
        auto objectIndex = selectRecordsList[selectedListIndex].row()  - indexOffset;

        main_vector.erase(objectIndex);
        ui->tableWidget->removeRow(objectIndex);

        indexOffset++;
    }

    ui->statusBar->showMessage(SELECTED_OBJECTS_DELETED_MESSAGE);
    setWindowTitle(WINDOW_TITLE_UNSAVED_SYMBOL + file_ + WINDOW_TITLE_TYPE_OBJECT);
}

//МЕТОД ОЧИСТКИ ВСЕЙ ТАБЛИЦЫ
void MainWindow::on_action_Clear_triggered()
{
    if (ui->tableWidget->rowCount() == 0) {
        ui->statusBar->showMessage(NO_OBJECTS_MESSAGE);
        return;
    }

    QMessageBox messageBox;

    messageBox.setWindowTitle(ATTENTION_MESSAGE);
    messageBox.setText(WARNING_WHEN_CLEAR_FULL_TABLE);
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);

    if (messageBox.exec() == QMessageBox::No) {
        return;
    }

    main_vector.clear();

    ui->tableWidget->setRowCount(0);

    ui->statusBar->showMessage(FULL_TABLE_CLEARED_MESSAGE);
    setWindowTitle(WINDOW_TITLE_UNSAVED_SYMBOL + file_ + WINDOW_TITLE_TYPE_OBJECT);
}

//МЕТОД ОТКРЫТИЯ ФАЙЛА
void MainWindow::on_action_Open_triggered(bool isCleanCurrentTable)
{
    QString file_name = QFileDialog::getOpenFileName(this, OPEN_FILE_MESSAGE_FIRST_PART, OPEN_FILE_MESSAGE_SECOND_PART, OPEN_FILE_MESSAGE_THIRD_PART);
    QFileInfo check_file(file_name);

    if (!check_file.exists() || !check_file.isFile())
    {
        ui->statusBar->showMessage(FILE_DOES_NOT_EXIST_MESSAGE_FIRST_PART + file_name + FILE_DOES_NOT_EXIST_MESSAGE_SECOND_PART);
        return;
    }

    if (isCleanCurrentTable) {
        MainWindow::on_action_New_triggered();
    }

    QFile file(file_name);

    if (!file.open(QIODevice::ReadOnly)) {
        ui->statusBar->showMessage(FILE_DOES_NOT_EXIST_MESSAGE_FIRST_PART + file_name + FILE_DOES_NOT_EXIST_MESSAGE_SECOND_PART);
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(DELIMITER);

        if (fields.size() != 4) { // Проверяем, что у строки 4 части: название, общее число мест, свободные места, год
            ui->statusBar->showMessage(INCORRECT_NUMBER_PROPERTIES_OBJECT);
            continue;
        }

        // Создаем объект RailwayCarriage
        RailwayCarriage record;
        record.setName(fields[0].simplified());
        record.setSeatCount(fields[1].simplified());
        record.setAvailableSeats(fields[2].simplified());
        record.setManufactureYear(fields[3].simplified());

        // Добавляем объект в контейнер
        main_vector.push_back(record);

        // Добавляем данные в таблицу
        int newRowIndex = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(newRowIndex);
        ui->tableWidget->setItem(newRowIndex, 0, new QTableWidgetItem(QString::number(newRowIndex + 1))); // Номер записи
        ui->tableWidget->setItem(newRowIndex, 1, new QTableWidgetItem(record.getName()));                 // Название
        ui->tableWidget->setItem(newRowIndex, 2, new QTableWidgetItem(record.getSeatCount()));            // Всего мест
        ui->tableWidget->setItem(newRowIndex, 3, new QTableWidgetItem(record.getAvailableSeats()));       // Свободные места
        ui->tableWidget->setItem(newRowIndex, 4, new QTableWidgetItem(record.getManufactureYear()));      // Год выпуска
    }

    file.close();
    file_ = file_name;

    ui->statusBar->showMessage(FILE_RECORDS_ADDED_MESSAGE);
    setWindowTitle(file_ + WINDOW_TITLE_TYPE_OBJECT);
}


//МЕТОД СОХРАНЕНИЯ ФАЙЛА
void MainWindow::on_action_Save_triggered()
{
    QFile file(file_);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        MainWindow::on_action_SaveAs_triggered();
        return;
    }

    QTextStream out(&file);

    int len = ui->tableWidget->rowCount();

    for (int i = 0; i < len; ++i) {
        QString recordNumber = ui->tableWidget->item(i, 0)->text();
        QString name = ui->tableWidget->item(i, 1)->text();
        QString seatCount = ui->tableWidget->item(i, 2)->text();
        QString availableSeats = ui->tableWidget->item(i, 3)->text();
        QString yearOfManufacture = ui->tableWidget->item(i, 4)->text();

        out << recordNumber << DELIMITER << name << DELIMITER << seatCount << DELIMITER << availableSeats << DELIMITER << yearOfManufacture << "\n";
    }

    file.close();

    ui->statusBar->showMessage(FILE_SAVED_MESSAGE);
    setWindowTitle(file_ + WINDOW_TITLE_TYPE_OBJECT);
}

//МЕТОД СОХРАНЕНИЯ ФАЙЛА КАК
void MainWindow::on_action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, SAVE_FILE_MESSAGE_FIRST_PART, SAVE_FILE_MESSAGE_SECOND_PART, SAVE_FILE_MESSAGE_THIRD_PART);

    if (file_name != "") {

        file_ = file_name;
        MainWindow::on_action_Save_triggered();
    }
}

//МЕТОД ОБЪЕДИНЕНИЯ ДАННОГО ФАЙЛА С ДРУГИМ
void MainWindow::on_action_Merge_triggered()
{
    QString current_file = file_;

    MainWindow::on_action_Open_triggered(false);
    file_ = current_file;

    ui->statusBar->showMessage(DATA_UNITED_MESSAGE);
    setWindowTitle(WINDOW_TITLE_UNSAVED_SYMBOL + file_ + WINDOW_TITLE_TYPE_OBJECT);
}

//МЕТОД АКТИВАЦИИ ИЗМЕНЕНИЯ ЗАПИСИ В ТАБЛИЦЕ ПУТЁМ ДВОЙНОГО НАЖАТИЯ НА ЗАПИСЬ
void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::on_action_Edit_triggered();
}

//МЕТОД ОТОБРАЖЕНИЯ ВСЕЙ ТАБЛИЦЫ В ФОРМАТЕ, В КОТОРОМ БУДЕТ ЗАПИСАНА В ФАЙЛ
void MainWindow::on_action_ShowData_triggered()
{
    ShowAllRecordsCode showDataDialogWindow;

    QString recordsInString;
    for (auto &record : main_vector) {
        recordsInString += record.getName() + DELIMITER + record.getSeatCount() + DELIMITER + record.getAvailableSeats() + DELIMITER + record.getManufactureYear() + "\n";

    }

    showDataDialogWindow.setText(recordsInString);
    showDataDialogWindow.exec();
}

//ВСПОМОГАТЕЛЬНЫЙ МЕТОД ОБНОВЛЕНИЯ ТАБЛИЦЫ И САМОГО ФАЙЛА
void MainWindow::createNewDatabase() {
    main_vector.clear();
    ui->tableWidget->setRowCount(0);
    file_ = "";

    setWindowTitle(WINDOW_TITLE_UNSAVED_SYMBOL + file_ + WINDOW_TITLE_TYPE_OBJECT);
}
