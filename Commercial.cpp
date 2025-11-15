#include "Commercial.h"

Commercial::Commercial(int decks, int pilots, int passengers_cap, double luggage_cap)
    : AircraftProduct(), numberof_decks{decks}, numberof_pilots{pilots},
    passengers_capacity{passengers_cap}, luggage_capacity{luggage_cap} {}

Commercial::Commercial()
    : Commercial(0,1,0,0) {}

Commercial::Commercial(int decks)
    : Commercial(decks,1,0,0) {}

Commercial::Commercial(int decks, int pilots)
    : Commercial(decks,pilots,0,0) {}

Commercial::Commercial(int decks, int pilots, int passengers_cap)
    : Commercial(decks,pilots,passengers_cap, 0) {}

Commercial::Commercial(const Commercial &other)
    : AircraftProduct(other),
    numberof_decks{other.numberof_decks},
    numberof_pilots{other.numberof_pilots},
    passengers_capacity{other.passengers_capacity},
    luggage_capacity{other.luggage_capacity} {}

Commercial::Commercial(Commercial &&other) noexcept
    : AircraftProduct(std::move(other)),
    numberof_decks{other.numberof_decks},
    numberof_pilots{other.numberof_pilots},
    passengers_capacity{other.passengers_capacity},
    luggage_capacity{other.luggage_capacity}
{
    other.numberof_decks = 0;
    other.numberof_pilots = 0;
    other.passengers_capacity = 0;
    other.luggage_capacity = 0;
}

Commercial::~Commercial() {
    qDebug() << "Commercial object was destroyed\n";
}

AircraftType Commercial::GetType() {
    return AircraftType::Commercial;
}

QJsonObject Commercial::toJson() const {
    QJsonObject object = AircraftProduct::toJson();
    object["numberof_decks"] = numberof_decks;
    object["numberof_pilots"] = numberof_pilots;
    object["passengers_capacity"] = passengers_capacity;
    object["luggage_capacity"] = luggage_capacity;
    return object;
}

void Commercial::fromJson(const QJsonObject &json) {
    AircraftProduct::fromJson(json);
    numberof_decks = json["numberof_decks"].toInt();
    numberof_pilots = json["numberof_pilots"].toInt();
    passengers_capacity = json["passengers_capacity"].toInt();
    luggage_capacity = json["luggage_capacity"].toDouble();
}

int Commercial::GetNumberof_decks() const {
    return numberof_decks;
}

void Commercial::SetNumberof_decks(int decks) {
    numberof_decks = decks;
}

int Commercial::GetNumberof_pilots() const {
    return numberof_pilots;
}

void Commercial::SetNumberof_pilots(int pilots) {
    numberof_pilots = pilots;
}

int Commercial::GetPassengers_capacity() const {
    return passengers_capacity;
}

void Commercial::SetPassengers_capacity(int new_cap) {
    passengers_capacity = new_cap;
}

double Commercial::GetLuggage_capacity() const {
    return luggage_capacity;
}

void Commercial::SetLuggage_capacity(double new_cap) {
    luggage_capacity = new_cap;
}

bool Commercial::CanFitPassengers(int passengers) const {
    return passengers <= passengers_capacity;
}

bool Commercial::CanFitLuggage(double luggage) const {
    return luggage <= luggage_capacity;
}
