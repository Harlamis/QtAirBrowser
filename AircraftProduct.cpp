#include "AircraftProduct.h"

AircraftProduct::AircraftProduct(QString mname, int mnumber, double new_max_speed, double price, int sold)
    : model_name{mname}, model_number{mnumber}, max_speed{new_max_speed}, price_per_unit{price}, sold_units{sold} {}

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
    model_name = other.model_name;
    model_number = other.model_number;
    max_speed = other.max_speed;
    price_per_unit = other.price_per_unit;
    sold_units = other.sold_units;
}

AircraftProduct::AircraftProduct(AircraftProduct &&other) noexcept {
    model_name = std::move(other.model_name);
    model_number = other.model_number;
    max_speed = other.max_speed;
    price_per_unit = other.price_per_unit;
    sold_units = other.sold_units;

    other.model_number = 0;
    other.max_speed = 0;
    other.price_per_unit = 0;
    other.sold_units = 0;
}

QString AircraftProduct::GetModelName() const {
    return model_name;
}

int AircraftProduct::GetModel_Number() const {
    return model_number;
}

double AircraftProduct::GetMax_speed() const {
    return max_speed;
}

double AircraftProduct::GetPrice() const {
    return price_per_unit;
}

int AircraftProduct::GetSold_units() const {
    return sold_units;
}

void AircraftProduct::SetModelName(const QString &input) {
    model_name = input;
}

void AircraftProduct::SetModel_Number(int input) {
    model_number = input;
}

void AircraftProduct::Set_Max_speed(double input) {
    max_speed = input;
}

void AircraftProduct::SetPrice(double input) {
    price_per_unit = input;
}

void AircraftProduct::SetSold_units(int input) {
    sold_units = input;
}

double AircraftProduct::RevenueCalc() const {
    return sold_units*price_per_unit;
}

QJsonObject AircraftProduct::toJson() const {
    QJsonObject json;
    json["model_name"] = model_name;
    json["model_number"] = model_number;
    json["max_speed"] = max_speed;
    json["price_per_unit"] = price_per_unit;
    json["sold_units"] = sold_units;
    return json;
}

void AircraftProduct::fromJson(const QJsonObject &json) {
    model_name = json["model_name"].toString();
    model_number = json["model_number"].toInt();
    max_speed = json["max_speed"].toDouble();
    price_per_unit = json["price_per_unit"].toDouble();
    sold_units = json["sold_units"].toInt();
    qDebug() << model_name << ": object loaded";
}
