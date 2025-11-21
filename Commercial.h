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

    int GetNumberof_decks() const;
    void SetNumberof_decks(int decks);

    int GetNumberof_pilots() const;
    void SetNumberof_pilots(int pilots);

    int GetPassengers_capacity() const;
    void SetPassengers_capacity(int new_cap);

    double GetLuggage_capacity() const;
    void SetLuggage_capacity(double new_cap);

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
