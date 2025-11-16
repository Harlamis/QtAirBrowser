#ifndef USER_H
#define USER_H

#include "BaseUser.h"
#include "AircraftDesigner.h"
#include <QList>
#include <QJsonArray>

class User : public BaseUser {
    QList<AircraftDesigner*> favourites;
public:
    virtual ~User() override;
    virtual QString GetRole() override;
    virtual QJsonObject toJson() override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // USER_H
