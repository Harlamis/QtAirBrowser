#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "AircraftProduct.h"
#include <QJsonObject>
#include <utility>
#include <QDebug>

/// @brief Represents a commercial aircraft.
/// Extends AircraftProduct with passenger and cargo capabilities.
class Commercial : public AircraftProduct {
    int numberOfDecks;
    int numberOfPilots;
    int passengersCapacity;
    double luggageCapacity;
public:
    Commercial(int decks, int pilots, int passengers_cap, double luggage_cap);
    Commercial();
    Commercial(int decks);
    Commercial(int decks, int pilots);
    Commercial(int decks, int pilots, int passengers_cap);

    Commercial(const Commercial &other);
    Commercial(Commercial &&other) noexcept;
    ~Commercial() override;

    /// @brief Returns "Commercial" type identifier.
    virtual QString GetType() const override;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;

    int GetNumberOfDecks() const;
    void SetNumberOfDecks(int decks);

    int GetNumberOfPilots() const;
    void SetNumberOfPilots(int pilots);

    int GetPassengersCapacity() const;
    void SetPassengerCapacity(int new_cap);

    double GetLuggageCapacity() const;
    void SetLuggageCapacity(double new_cap);

    /// @brief Checks if the plane fits a certain number of passengers.
    /// @param passengers Number of people.
    /// @return True if capacity is sufficient.
    bool CanFitPassengers(int passengers) const;

    /// @brief Checks if the plane fits a certain amount of luggage.
    /// @param luggage Amount of luggage.
    /// @return True if capacity is sufficient.
    bool CanFitLuggage(double luggage) const;
};
#endif // COMMERCIAL_H
