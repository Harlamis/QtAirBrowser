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
public:
    AircraftProduct(QString mname, int mnumber, double new_max_speed)
        : model_name{mname}, model_number{mnumber}, max_speed{new_max_speed} {};
    AircraftProduct(QString mname)
        : AircraftProduct(mname, 0,0) {};
    AircraftProduct(QString mname, int mnumber)
        :AircraftProduct(mname,mnumber,0) {};
    AircraftProduct()
        : AircraftProduct("", 0,0) {};
    virtual ~AircraftProduct() {
        qDebug() << "Aircraft was destroyed\n";
    }

    AircraftProduct(AircraftProduct &other) {
        model_name = other.model_name;
        model_number = other.model_number;
        max_speed = other.max_speed;
    }

    AircraftProduct(AircraftProduct &&other) {
        model_name = std::move(other.model_name);
        model_number = std::move(other.model_number);
        max_speed = std::move(other.max_speed);
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

    void SetModelName(const QString &input) {
        model_name = input;
    }

    void SetModel_Number(const int &input) {
        model_number = input;
    }

    void Set_Max_speed(const double &input) {
        max_speed = input;
    }

    virtual AircraftType GetType() = 0;

    virtual QJsonObject toJson() override {
        QJsonObject json;
        json["model_name"] = model_name;
        json["model_number"] = model_number;
        return json;
    }
};
