#ifndef AIRCRAFTPRODUCT_H
#define AIRCRAFTPRODUCT_H

#include <QString>
#include <QJsonObject>
#include <QDebug>
#include <utility>
#include "ISerializable.h"

/// @brief Abstract base class for all aircraft products.
/// Contains common properties like model name, speed, and price.
class AircraftProduct : public ISerializable {
    QString model_name;
    int model_number;
    double max_speed;
    double price_per_unit;
    int sold_units;
public:
    AircraftProduct(QString mname, int mnumber, double new_max_speed, double price, int sold);
    AircraftProduct(QString mname);
    AircraftProduct(QString mname, int mnumber);
    AircraftProduct(QString mname, int mnumber, double max_speed);
    AircraftProduct(QString mname, int mnumber, double max_speed, double price);
    AircraftProduct();
    virtual ~AircraftProduct();

    AircraftProduct(const AircraftProduct &other);
    AircraftProduct(AircraftProduct &&other) noexcept;

    /// @brief Gets the name of the model.
    /// @return The model name string.
    QString GetModelName() const;

    /// @brief Gets the internal model number.
    /// @return The model number.
    int GetModel_Number() const;

    /// @brief Gets the maximum speed of the aircraft.
    /// @return Speed in km/h.
    double GetMax_speed() const;

    /// @brief Gets the price per unit.
    /// @return Price in currency.
    double GetPrice() const;

    /// @brief Gets the number of sold units.
    /// @return The count of sold units.
    int GetSold_units() const;

    /// @brief Sets the model name.
    /// @param input The new name.
    void SetModelName(const QString &input);

    /// @brief Sets the model number.
    /// @param input The new model number.
    void SetModel_Number(int input);

    /// @brief Sets the maximum speed.
    /// @param input The new speed in km/h.
    void Set_Max_speed(double input);

    /// @brief Sets the price per unit.
    /// @param input The new price.
    void SetPrice(double input);

    /// @brief Sets the number of sold units.
    /// @param input The quantity sold.
    void SetSold_units(int input);

    /// @brief Calculates total revenue for this product.
    /// @return Price multiplied by sold units.
    double RevenueCalc() const;

    /// @brief Returns the specific type of the aircraft.
    /// @return A string like "Commercial" or "Fighter".
    virtual QString GetType() const = 0;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // AIRCRAFTPRODUCT_H
