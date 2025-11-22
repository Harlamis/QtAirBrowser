#include "Commercial.h"

Commercial::Commercial(int decks, int pilots, int passengers_cap, double luggage_cap)
    : AircraftProduct(), numberOfDecks{decks}, numberOfPilots{pilots},
    passengersCapacity{passengers_cap}, luggageCapacity{luggage_cap} {}

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
    numberOfDecks{other.numberOfDecks},
    numberOfPilots{other.numberOfPilots},
    passengersCapacity{other.passengersCapacity},
    luggageCapacity{other.luggageCapacity} {}

Commercial::Commercial(Commercial &&other) noexcept
    : AircraftProduct(std::move(other)),
    numberOfDecks{other.numberOfDecks},
    numberOfPilots{other.numberOfPilots},
    passengersCapacity{other.passengersCapacity},
    luggageCapacity{other.luggageCapacity}
{
    other.numberOfDecks = 0;
    other.numberOfPilots = 0;
    other.passengersCapacity = 0;
    other.luggageCapacity = 0;
}

Commercial::~Commercial() {
    qDebug() << "Commercial object was destroyed\n";
}

QString Commercial::GetType() const {
    return "Commercial";
}

QJsonObject Commercial::toJson() const {
    QJsonObject object = AircraftProduct::toJson();
    object["numberof_decks"] = numberOfDecks;
    object["numberof_pilots"] = numberOfPilots;
    object["passengers_capacity"] = passengersCapacity;
    object["luggage_capacity"] = luggageCapacity;
    return object;
}

void Commercial::fromJson(const QJsonObject &json) {
    AircraftProduct::fromJson(json);
    numberOfDecks = json["numberof_decks"].toInt();
    numberOfPilots = json["numberof_pilots"].toInt();
    passengersCapacity = json["passengers_capacity"].toInt();
    luggageCapacity = json["luggage_capacity"].toDouble();
}

int Commercial::GetNumberof_decks() const {
    return numberOfDecks;
}

void Commercial::SetNumberof_decks(int decks) {
    numberOfDecks = decks;
}

int Commercial::GetNumberof_pilots() const {
    return numberOfPilots;
}

void Commercial::SetNumberof_pilots(int pilots) {
    numberOfPilots = pilots;
}

int Commercial::GetPassengers_capacity() const {
    return passengersCapacity;
}

void Commercial::SetPassengers_capacity(int new_cap) {
    passengersCapacity = new_cap;
}

double Commercial::GetLuggage_capacity() const {
    return luggageCapacity;
}

void Commercial::SetLuggage_capacity(double new_cap) {
    luggageCapacity = new_cap;
}

bool Commercial::CanFitPassengers(int passengers) const {
    return passengers <= passengersCapacity;
}

bool Commercial::CanFitLuggage(double luggage) const {
    return luggage <= luggageCapacity;
}
