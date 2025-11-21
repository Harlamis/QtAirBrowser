#include "AircraftProduct.h"

AircraftProduct::AircraftProduct(QString mname, int mnumber, double new_max_speed, double price, int sold)
    : modelName{mname}, modelNumber{mnumber}, maxSpeed{new_max_speed}, pricePerUnit{price}, soldUnits{sold} {}

AircraftProduct::AircraftProduct(QString mname)
    : AircraftProduct(mname, 0,0,0,0) {}

AircraftProduct::AircraftProduct(QString mname, int mnumber)
    :AircraftProduct(mname,mnumber,0,0,0) {}

AircraftProduct::AircraftProduct(QString mname, int mnumber, double max_speed)
    : AircraftProduct(mname,mnumber,max_speed,0,0) {}

AircraftProduct::AircraftProduct(QString mname, int mnumber, double max_speed, double price)
    : AircraftProduct(mname,mnumber,max_speed,price,0) {}

AircraftProduct::AircraftProduct()
    : AircraftProduct("", 0,0,0,0) {}

AircraftProduct::~AircraftProduct() {
    qDebug() << "Aircraft was destroyed\n";
}

AircraftProduct::AircraftProduct(const AircraftProduct &other) {
    modelName = other.modelName;
    modelNumber = other.modelNumber;
    maxSpeed = other.maxSpeed;
    pricePerUnit = other.pricePerUnit;
    soldUnits = other.soldUnits;
}

AircraftProduct::AircraftProduct(AircraftProduct &&other) noexcept {
    modelName = std::move(other.modelName);
    modelNumber = other.modelNumber;
    maxSpeed = other.maxSpeed;
    pricePerUnit = other.pricePerUnit;
    soldUnits = other.soldUnits;

    other.modelNumber = 0;
    other.maxSpeed = 0;
    other.pricePerUnit = 0;
    other.soldUnits = 0;
}

QString AircraftProduct::GetModelName() const {
    return modelName;
}

int AircraftProduct::GetModel_Number() const {
    return modelNumber;
}

double AircraftProduct::GetMax_speed() const {
    return maxSpeed;
}

double AircraftProduct::GetPrice() const {
    return pricePerUnit;
}

int AircraftProduct::GetSold_units() const {
    return soldUnits;
}

void AircraftProduct::SetModelName(const QString &input) {
    modelName = input;
}

void AircraftProduct::SetModel_Number(int input) {
    modelNumber = input;
}

void AircraftProduct::Set_Max_speed(double input) {
    maxSpeed = input;
}

void AircraftProduct::SetPrice(double input) {
    pricePerUnit = input;
}

void AircraftProduct::SetSold_units(int input) {
    soldUnits = input;
}

double AircraftProduct::RevenueCalc() const {
    return soldUnits*pricePerUnit;
}

QJsonObject AircraftProduct::toJson() const {
    QJsonObject json;
    json["model_name"] = modelName;
    json["model_number"] = modelNumber;
    json["max_speed"] = maxSpeed;
    json["price_per_unit"] = pricePerUnit;
    json["sold_units"] = soldUnits;
    return json;
}

void AircraftProduct::fromJson(const QJsonObject &json) {
    modelName = json["model_name"].toString();
    modelNumber = json["model_number"].toInt();
    maxSpeed = json["max_speed"].toDouble();
    pricePerUnit = json["price_per_unit"].toDouble();
    soldUnits = json["sold_units"].toInt();
    qDebug() << modelName << ": object loaded";
}
