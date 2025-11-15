#ifndef AIRCRAFTPRODUCT_H
#define AIRCRAFTPRODUCT_H

#include <QString>
#include <QJsonObject>
#include <QDebug>
#include <utility>
#include "ISerializable.h"

class AircraftProduct : public ISerializable {
    QString model_name;
    int model_number;
    double max_speed;
    double price_per_unit;
    int sold_units;
public:
    AircraftProduct(QString mname, int mnumber, double new_max_speed, double price, int sold);
    AircraftProduct(QString mname);
    AircraftProduct(QString mname, int mnumber);
    AircraftProduct(QString mname, int mnumber, double max_speed);
    AircraftProduct(QString mname, int mnumber, double max_speed, double price);
    AircraftProduct();
    virtual ~AircraftProduct();

    AircraftProduct(const AircraftProduct &other);
    AircraftProduct(AircraftProduct &&other) noexcept;

    QString GetModelName() const;
    int GetModel_Number() const;
    double GetMax_speed() const;
    double GetPrice() const;
    int GetSold_units() const;

    void SetModelName(const QString &input);
    void SetModel_Number(int input);
    void Set_Max_speed(double input);
    void SetPrice(double input);
    void SetSold_units(int input);

    double RevenueCalc() const;

    virtual QString GetType() const = 0;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // AIRCRAFTPRODUCT_H
