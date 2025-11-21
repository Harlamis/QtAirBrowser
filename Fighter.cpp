#include "Fighter.h"
#include <QJsonObject>
#include <QDebug>
#include <utility>

Fighter::Fighter(double stealth_r, double ammo_c, double mf_height)
    : AircraftProduct(),
    stealthRange{stealth_r},
    ammoCapacity{ammo_c},
    maxFlightHeight{mf_height} {}

Fighter::Fighter(double stealth_r, double ammo_c)
    : Fighter(stealth_r, ammo_c, 0.0) {}

Fighter::Fighter(double stealth_r)
    : Fighter(stealth_r, 0.0, 0.0) {}

Fighter::Fighter()
    : Fighter(0.0, 0.0, 0.0) {}

Fighter::Fighter(const Fighter &other)
    : AircraftProduct(other),
    stealthRange{other.stealthRange},
    ammoCapacity{other.ammoCapacity},
    maxFlightHeight{other.maxFlightHeight} {}

Fighter::Fighter(Fighter &&other) noexcept
    : AircraftProduct(std::move(other)),
    stealthRange{other.stealthRange},
    ammoCapacity{other.ammoCapacity},
    maxFlightHeight{other.maxFlightHeight}
{
    other.stealthRange = 0.0;
    other.ammoCapacity = 0.0;
    other.maxFlightHeight = 0.0;
}

Fighter::~Fighter() {
    qDebug() << "Fighter object was destroyed\n";
}

QString Fighter::GetType() const {
    return "Fighter";
}

QJsonObject Fighter::toJson() const {
    QJsonObject object = AircraftProduct::toJson();
    object["stealth_range"] = stealthRange;
    object["ammo_capacity"] = ammoCapacity;
    object["max_flight_height"] = maxFlightHeight;
    return object;
}

void Fighter::fromJson(const QJsonObject &json) {
    AircraftProduct::fromJson(json);
    stealthRange = json["stealth_range"].toDouble();
    ammoCapacity = json["ammo_capacity"].toDouble();
    maxFlightHeight = json["max_flight_height"].toDouble();
}

double Fighter::GetStealthRange() const {
    return stealthRange;
}

void Fighter::SetStealthRange(double range) {
    stealthRange = range;
}

double Fighter::GetAmmoCapacity() const {
    return ammoCapacity;
}

void Fighter::SetAmmoCapacity(double cap) {
    ammoCapacity = cap;
}

double Fighter::GetMaxFlightHeight() const {
    return maxFlightHeight;
}

void Fighter::SetMaxFlightHeight(double height) {
    maxFlightHeight = height;
}

bool Fighter::CanReach(double height) const {
    return height <= maxFlightHeight;
}

bool Fighter::CanFitAmmo(double ammo) const {
    return ammo <= ammoCapacity;
}
