#ifndef AIRCRAFTPRODUCT_H
#define AIRCRAFTPRODUCT_H
#include <QString>
#include "ISerializable.h"
#include <QJsonObject>
#include <utility>
#endif // AIRCRAFTPRODUCT_H

enum AircraftType {
    Commercial,
    Jet,
    Fighter,
    UAV,
};

class AircraftProduct : public ISerializable {
    QString model_name;
    int model_number;
    double max_speed;
    double price_per_unit;
    int sold_units;
public:
    AircraftProduct(QString mname, int mnumber, double new_max_speed, double price, int sold)
        : model_name{mname}, model_number{mnumber}, max_speed{new_max_speed}, price_per_unit{price}, sold_units{sold} {};
    AircraftProduct(QString mname)
        : AircraftProduct(mname, 0,0,0,0) {};
    AircraftProduct(QString mname, int mnumber)
        :AircraftProduct(mname,mnumber,0,0,0) {};
    AircraftProduct(QString mname, int mnumber, double max_speed)
        : AircraftProduct(mname,mnumber,max_speed,0,0) {};
    AircraftProduct(QString mname, int mnumber, double max_speed, double price)
        : AircraftProduct(mname,mnumber,max_speed,price,0) {};
    AircraftProduct()
        : AircraftProduct("", 0,0,0,0) {};
    virtual ~AircraftProduct() {
        qDebug() << "Aircraft was destroyed\n";
    }

    AircraftProduct(AircraftProduct &other) {
        model_name = other.model_name;
        model_number = other.model_number;
        max_speed = other.max_speed;
        price_per_unit = other.price_per_unit;
        sold_units = other.sold_units;
    }

    AircraftProduct(AircraftProduct &&other) {
        model_name = std::move(other.model_name);
        model_number = std::move(other.model_number);
        max_speed = std::move(other.max_speed);
        price_per_unit =std::move(other.price_per_unit);
        sold_units = std::move(other.sold_units);
    }
    QString GetModelName() {
        return model_name;
    }

    int GetModel_Number() {
        return model_number;
    }

    double GetMax_speed() {
        return max_speed;
    }

    double GetPrice() {
        return price_per_unit;
    }

    int GetSold_units() {
        return sold_units;
    }

    void SetModelName(const QString &input) {
        model_name = input;
    }

    void SetModel_Number(const int &input) {
        model_number = input;
    }

    void Set_Max_speed(const double &input) {
        max_speed = input;
    }

    void SetPrice(double &input) {
        price_per_unit = input;
    }

    void SetSold_units(int &input) {
        sold_units = input;
    }

    double RevenueCalc() {
        return sold_units*price_per_unit;
    }

    virtual AircraftType GetType() = 0;

    virtual QJsonObject toJson() override {
        QJsonObject json;
        json["model_name"] = model_name;
        json["model_number"] = model_number;
        json["max_speed"] = max_speed;
        json["price_per_unit"] = price_per_unit;
        json["sold_units"] = sold_units;
        return json;
    }
};
