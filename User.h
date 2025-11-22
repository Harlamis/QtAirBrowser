#ifndef USER_H
#define USER_H

#include "BaseUser.h"
#include <QList>
#include <QJsonArray>
#include <QJsonObject>

class AircraftDesigner;

/// @brief Represents a standard user with a favorites list.
class User : public BaseUser {
public:
    User();
    User(QString new_name, QString new_login, QString new_password);

    virtual ~User() override;
    User(const User& other);
    User& operator=(const User& other);
    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    /// @brief Returns "User".
    virtual QString GetRole() const override;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // USER_H
