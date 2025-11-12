#ifndef BASEUSER_H
#define BASEUSER_H
#include <qstring.h>
#include "ISerializable.h"
#include <QJsonObject>

#endif // BASEUSER_H

enum UserRole {
    User,
    Admin
};

class BaseUser : public ISerializable {
    QString name;
    QString login;
    QString password;
public:
    BaseUser() : name{""}, login{""}, password{""} {};
    BaseUser(QString new_name, QString new_login, QString new_password) : name{new_name}, login{new_login}, password{new_password} {};
    QString GetName() {
        return name;
    }

    QString GetLogin() {
        return login;
    }

    QString GetPassword() {
        return password;
    }

    void SetName(const QString &input) {
        name = input;
    }

    void SetLogin(const QString &input) {
        login = input;
    }

    void SetPassword(const QString &input) {
        password = input;
    }

    bool CheckPassword(const QString input) {
        return input == password;
    }

    virtual UserRole GetRole() = 0;

    virtual QJsonObject toJson() override {
        QJsonObject json;
        json["name"] = name;
        json["login"] = login;
        json["password"] = password;
        return json;
    }

    virtual void fromJson(const QJsonObject &json) override {
        name = json["name"].toString();
        login = json["login"].toString();
        password = json["password"].toString();
    }
};
