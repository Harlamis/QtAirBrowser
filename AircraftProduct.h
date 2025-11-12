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
public:
    AircraftProduct(QString mname, int mnumber)
        : model_name{mname}, model_number{mnumber} {};
    AircraftProduct(QString mname)
        : AircraftProduct(mname, 0) {};
    AircraftProduct()
        : AircraftProduct("", 0) {};
    virtual ~AircraftProduct() {
        qDebug() << "Aircraft was destroyed\n";
    }

    AircraftProduct(AircraftProduct &other) {
        model_name = other.model_name;
        model_number = other.model_number;
    }

    AircraftProduct(AircraftProduct &&other) {
        model_name = std::move(other.model_name);
        model_number = std::move(other.model_number);
    }
    QString GetModelName() {
        return model_name;
    }

    int GetModel_Number() {
        return model_number;
    }

    virtual AircraftType GetType() = 0;

    virtual QJsonObject toJson() override {
        QJsonObject json;
        json["model_name"] = model_name;
        json["model_number"] = model_number;
        return json;
    }
};
