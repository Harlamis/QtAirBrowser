#include "BaseUser.h"

BaseUser::BaseUser() : name{""}, login{""}, password{""} {}

BaseUser::BaseUser(QString new_name, QString new_login, QString new_password)
    : name{new_name}, login{new_login}, password{new_password} {}

QString BaseUser::GetName() const {
    return name;
}

QString BaseUser::GetLogin() const {
    return login;
}

QString BaseUser::GetPassword() const {
    return password;
}

void BaseUser::SetName(const QString &input) {
    name = input;
}

void BaseUser::SetLogin(const QString &input) {
    login = input;
}

void BaseUser::SetPassword(const QString &input) {
    password = input;
}

bool BaseUser::CheckPassword(const QString input) const {
    return input == password;
}

QJsonObject BaseUser::toJson() {
    QJsonObject json;
    json["name"] = name;
    json["login"] = login;
    json["password"] = password;
    return json;
}

void BaseUser::fromJson(const QJsonObject &json) {
    name = json["name"].toString();
    login = json["login"].toString();
    password = json["password"].toString();
}
