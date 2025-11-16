#ifndef USER_H
#define USER_H

#include "BaseUser.h"
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class AircraftDesigner;

class User : public BaseUser {
    QList<AircraftDesigner*> favourites;

public:
    User();
    User(QString new_name, QString new_login, QString new_password);

    virtual ~User() override;
    User(const User& other);
    User& operator=(const User& other);
    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    virtual QString GetRole() const override;
    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;

    void AddFavourite(AircraftDesigner* designer);
    bool RemoveFavourite(const QString& designerName);
    QList<AircraftDesigner*> GetFavourites() const;
};

#endif // USER_H
