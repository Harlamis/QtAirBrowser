#include "Fighter.h"
#include <QJsonObject>
#include <QDebug>
#include <utility>

Fighter::Fighter(double stealth_r, double ammo_c, double mf_height)
    : AircraftProduct(),
    stealth_range{stealth_r},
    ammo_capacity{ammo_c},
    max_flight_height{mf_height} {}

Fighter::Fighter(double stealth_r, double ammo_c)
    : Fighter(stealth_r, ammo_c, 0.0) {}

Fighter::Fighter(double stealth_r)
    : Fighter(stealth_r, 0.0, 0.0) {}

Fighter::Fighter()
    : Fighter(0.0, 0.0, 0.0) {}

Fighter::Fighter(const Fighter &other)
    : AircraftProduct(other),
    stealth_range{other.stealth_range},
    ammo_capacity{other.ammo_capacity},
    max_flight_height{other.max_flight_height} {}

Fighter::Fighter(Fighter &&other) noexcept
    : AircraftProduct(std::move(other)),
    stealth_range{other.stealth_range},
    ammo_capacity{other.ammo_capacity},
    max_flight_height{other.max_flight_height}
{
    other.stealth_range = 0.0;
    other.ammo_capacity = 0.0;
    other.max_flight_height = 0.0;
}

Fighter::~Fighter() {
    qDebug() << "Fighter object was destroyed\n";
}

QString Fighter::GetType() const {
    return "Fighter";
}

QJsonObject Fighter::toJson() const {
    QJsonObject object = AircraftProduct::toJson();
    object["stealth_range"] = stealth_range;
    object["ammo_capacity"] = ammo_capacity;
    object["max_flight_height"] = max_flight_height;
    return object;
}

void Fighter::fromJson(const QJsonObject &json) {
    AircraftProduct::fromJson(json);
    stealth_range = json["stealth_range"].toDouble();
    ammo_capacity = json["ammo_capacity"].toDouble();
    max_flight_height = json["max_flight_height"].toDouble();
}

double Fighter::GetStealth_range() const {
    return stealth_range;
}

void Fighter::SetStealth_range(double range) {
    stealth_range = range;
}

double Fighter::GetAmmo_capacity() const {
    return ammo_capacity;
}

void Fighter::SetAmmo_capacity(double cap) {
    ammo_capacity = cap;
}

double Fighter::GetMax_flight_height() const {
    return max_flight_height;
}

void Fighter::SetMax_flight_height(double height) {
    max_flight_height = height;
}

bool Fighter::CanReach(double height) const {
    return height <= max_flight_height;
}

bool Fighter::CanFitAmmo(double ammo) const {
    return ammo <= ammo_capacity;
}
