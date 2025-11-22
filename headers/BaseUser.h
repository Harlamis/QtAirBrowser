#ifndef BASEUSER_H
#define BASEUSER_H

#include <QString>
#include <QJsonObject>
#include "ISerializable.h"

/// @brief Abstract base class for users (Admin and User).
class BaseUser : public ISerializable {
    QString name;
    QString login;
    QString password;
public:
    BaseUser();
    BaseUser(QString new_name, QString new_login, QString new_password);
    virtual ~BaseUser() {}

    /// @brief Gets the user's full name.
    QString GetName() const;

    /// @brief Gets the user's login.
    QString GetLogin() const;

    /// @brief Gets the user's password.
    QString GetPassword() const;

    void SetName(const QString &input);
    void SetLogin(const QString &input);
    void SetPassword(const QString &input);

    /// @brief Verifies the password.
    /// @param input The password to check.
    /// @return True if matches.
    bool CheckPassword(const QString input) const;

    /// @brief Returns the user's role.
    virtual QString GetRole() const = 0;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // BASEUSER_H
