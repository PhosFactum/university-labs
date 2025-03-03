#ifndef RAILWAYCARRIAGE_H
#define RAILWAYCARRIAGE_H

#include <QString>

class RailwayCarriage {
private:
    QString name;
    QString seatCount;
    QString availableSeats;
    QString manufactureYear;

public:
    RailwayCarriage();
    explicit RailwayCarriage(const QString& carriageName, const QString& seatCount, const QString& availableSeats, const QString& manufactureYear);

    RailwayCarriage(const RailwayCarriage &selectedRecord);
    RailwayCarriage &operator=(const RailwayCarriage &selectedRecord);
    RailwayCarriage(RailwayCarriage &&selectedRecord) noexcept;
    RailwayCarriage &operator=(RailwayCarriage &&selectedRecord) noexcept;
    virtual ~RailwayCarriage();

    void setName(const QString& nameValue);
    void setSeatCount(const QString& seatCountValue);
    void setAvailableSeats(const QString& availableSeatsValue);
    void setManufactureYear(const QString& manufactureYearValue);

    const QString& getName() const;
    const QString& getSeatCount() const;
    const QString& getAvailableSeats() const;
    const QString& getManufactureYear() const;
};

#endif // RAILWAYCARRIAGE_H
