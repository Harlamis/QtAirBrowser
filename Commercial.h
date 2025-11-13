#ifndef COMMERCIAL_H
#define COMMERCIAL_H
#include "AircraftProduct.h"
#include "QJsonObject"
#include <utility>
#endif // COMMERCIAL_H

class Commercial : public AircraftProduct {
    int numberof_decks;
    int numberof_pilots;
    int passengers_capacity;
    double luggage_capacity;
public:
    Commercial(int decks, int pilots, int passengers_cap, double luggage_cap)
        : AircraftProduct(), numberof_decks{decks}, numberof_pilots{pilots},
        luggage_capacity{luggage_cap}, passengers_capacity{passengers_cap} {};

    Commercial()
        : Commercial(0,1,0,0) {};

    Commercial(int decks)
        : Commercial(decks,1,0,0) {};

    Commercial(int decks, int pilots)
        : Commercial(decks,pilots,0,0) {};

    Commercial(int decks, int pilots, int passengers_cap)
        : Commercial(decks,pilots,passengers_cap, 0) {};

    Commercial(Commercial &other)
        : AircraftProduct(other),
        numberof_decks{other.numberof_decks},
        numberof_pilots{other.numberof_pilots},
        passengers_capacity{other.passengers_capacity},
        luggage_capacity{other.luggage_capacity} {};

    Commercial(Commercial &&other)
        : AircraftProduct(std::move(other)),
        numberof_decks{other.numberof_decks},
        numberof_pilots{other.numberof_pilots},
        passengers_capacity{other.passengers_capacity},
        luggage_capacity{other.luggage_capacity} {};

    ~Commercial() override {
        qDebug() << "Commercial object was destroyed\n";
    }

    virtual AircraftType GetType() override {
        return AircraftType::Commercial;
    }

    int GetNumberof_decks() {
        return numberof_decks;
    }

    void SetNumberof_decks(int decks) {
        numberof_decks = decks;
    }

    int GetNumberof_pilots() {
        return numberof_pilots;
    }

    void SetNumberof_pilots(int pilots) {
        numberof_pilots = pilots;
    }

    int GetPassengers_capacity() {
        return passengers_capacity;
    }

    void SetPassengers_capacity(int new_cap) {
        passengers_capacity = new_cap;
    }

    int GetLuggage_capacity() {
        return luggage_capacity;
    }

    void SetLuggage_capacity(int new_cap) {
        luggage_capacity = new_cap;
    }

    bool CanFitPassengers(int passengers) {
        return passengers <= passengers_capacity;
    }

    bool CanFitLuggage(double luggage) {
        return luggage <= luggage_capacity;
    }
};
