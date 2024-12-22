#include "RailwayCarriage.h"

// Конструктор по умолчанию
RailwayCarriage::RailwayCarriage()
    : name(""), seatCount(""), availableSeats(""), manufactureYear("") {}

// Конструктор с параметрами
RailwayCarriage::RailwayCarriage(const QString& carriageName, const QString& seatCount, const QString& availableSeats, const QString& manufactureYear)
    : name(carriageName), seatCount(seatCount), availableSeats(availableSeats), manufactureYear(manufactureYear) {}

// Конструктор копирования
RailwayCarriage::RailwayCarriage(const RailwayCarriage &selectedRecord)
    : name(selectedRecord.name), seatCount(selectedRecord.seatCount), availableSeats(selectedRecord.availableSeats), manufactureYear(selectedRecord.manufactureYear) {}

// Оператор присваивания (копирование)
RailwayCarriage& RailwayCarriage::operator=(const RailwayCarriage &selectedRecord) {
    if (this != &selectedRecord) {  // Проверка на самоприсваивание
        name = selectedRecord.name;
        seatCount = selectedRecord.seatCount;
        availableSeats = selectedRecord.availableSeats;
        manufactureYear = selectedRecord.manufactureYear;
    }
    return *this;
}

// Конструктор перемещения
RailwayCarriage::RailwayCarriage(RailwayCarriage &&selectedRecord) noexcept
    : name(std::move(selectedRecord.name)), seatCount(std::move(selectedRecord.seatCount)),
    availableSeats(std::move(selectedRecord.availableSeats)), manufactureYear(std::move(selectedRecord.manufactureYear)) {}

// Оператор присваивания (перемещение)
RailwayCarriage& RailwayCarriage::operator=(RailwayCarriage &&selectedRecord) noexcept {
    if (this != &selectedRecord) {  // Проверка на самоприсваивание
        name = std::move(selectedRecord.name);
        seatCount = std::move(selectedRecord.seatCount);
        availableSeats = std::move(selectedRecord.availableSeats);
        manufactureYear = std::move(selectedRecord.manufactureYear);
    }
    return *this;
}

// Деструктор
RailwayCarriage::~RailwayCarriage() {}

// Сеттеры
void RailwayCarriage::setName(const QString& nameValue) {
    name = nameValue;
}

void RailwayCarriage::setSeatCount(const QString& seatCountValue) {
    seatCount = seatCountValue;
}

void RailwayCarriage::setAvailableSeats(const QString& availableSeatsValue) {
    availableSeats = availableSeatsValue;
}

void RailwayCarriage::setManufactureYear(const QString& manufactureYearValue) {
    manufactureYear = manufactureYearValue;
}

// Геттеры
const QString& RailwayCarriage::getName() const {
    return name;
}

const QString& RailwayCarriage::getSeatCount() const {
    return seatCount;
}

const QString& RailwayCarriage::getAvailableSeats() const {
    return availableSeats;
}

const QString& RailwayCarriage::getManufactureYear() const {
    return manufactureYear;
}
