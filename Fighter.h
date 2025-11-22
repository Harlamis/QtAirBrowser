
#ifndef FIGHTER_H
#define FIGHTER_H

#include "AircraftProduct.h"

/// @brief Represents a military fighter aircraft.
/// Extends AircraftProduct with combat specifications.
class Fighter : public AircraftProduct {
    double stealthRange;
    double ammoCapacity;
    double maxFlightHeight;
public:
    Fighter();
    Fighter(double stealth_r);
    Fighter(double stealth_r, double ammo_c);
    Fighter(double stealth_r, double ammo_c, double mf_height);
    Fighter(const Fighter &other);
    Fighter(Fighter &&other) noexcept;
    ~Fighter() override;

    /// @brief Returns "Fighter" type identifier.
    virtual QString GetType() const override;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;

    double GetStealthRange() const;
    void SetStealthRange(double range);

    double GetAmmoCapacity() const;
    void SetAmmoCapacity(double cap);

    double GetMaxFlightHeight() const;
    void SetMaxFlightHeight(double height);
};

#endif // FIGHTER_H
