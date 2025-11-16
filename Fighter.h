#ifndef FIGHTER_H
#define FIGHTER_H

#include "AircraftProduct.h"

class Fighter : public AircraftProduct {
    double stealth_range;
    double ammo_capacity;
    double max_flight_height;
public:
    Fighter();
    Fighter(double stealth_r);
    Fighter(double stealth_r, double ammo_c);
    Fighter(double stealth_r, double ammo_c, double mf_height);
    Fighter(const Fighter &other);
    Fighter(Fighter &&other) noexcept;
    ~Fighter() override;
    virtual QString GetType() const override;
    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;

    double GetStealth_range() const;
    void SetStealth_range(double range);
    double GetAmmo_capacity() const;
    void SetAmmo_capacity(double cap);
    double GetMax_flight_height() const;
    void SetMax_flight_height(double height);

    bool CanReach(double height) const;
    bool CanFitAmmo(double ammo) const;
};

#endif // FIGHTER_H
