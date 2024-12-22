#include "MainWindow.h"
#include <QApplication>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Создаем объект приложения, передавая аргументы командной строки
    QApplication::setStyle("Windows");

    MainWindow w; // Создаем экземпляр основного окна

    // Устанавливаем иконку для окна приложения из ресурсов
    QIcon icon(":/images/icons/main_icon.png"); // Путь к иконке в ресурсах проекта
    a.setWindowIcon(icon); // Применяем иконку к приложению

    w.show(); // Отображаем главное окно

    return a.exec(); // Запускаем главный цикл обработки событий приложения
}
