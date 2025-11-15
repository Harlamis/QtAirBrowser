#ifndef BASEUSER_H
#define BASEUSER_H

#include <QString>
#include <QJsonObject>
#include "ISerializable.h"

enum UserRole {
    User,
    Admin
};

class BaseUser : public ISerializable {
    QString name;
    QString login;
    QString password;
public:
    BaseUser();
    BaseUser(QString new_name, QString new_login, QString new_password);
    virtual ~BaseUser() {}

    QString GetName() const;
    QString GetLogin() const;
    QString GetPassword() const;

    void SetName(const QString &input);
    void SetLogin(const QString &input);
    void SetPassword(const QString &input);

    bool CheckPassword(const QString input) const;

    virtual UserRole GetRole() = 0;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // BASEUSER_H
