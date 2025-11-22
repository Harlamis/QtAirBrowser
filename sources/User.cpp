#include "User.h"
#include "AircraftDesigner.h"
#include <QtAlgorithms>
#include <QJsonArray>
#include <QDebug>
#include <utility>
#include <QtGlobal>

User::User() : BaseUser() {}

User::User(QString new_name, QString new_login, QString new_password)
    : BaseUser(new_name, new_login, new_password) {}

User::~User() {
}

User::User(const User& other) : BaseUser(other) {
}

User& User::operator=(const User& other) {
    if (this == &other) {
        return *this;
    }
    BaseUser::operator=(other);
    return *this;
}

User::User(User&& other) noexcept
    : BaseUser(std::move(other)) {
}

User& User::operator=(User&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    BaseUser::operator=(std::move(other));
    return *this;
}

QString User::GetRole() const {
    return "User";
}

QJsonObject User::toJson() const {
    QJsonObject json = BaseUser::toJson();
    json["_role"] = GetRole();

    return json;
}

void User::fromJson(const QJsonObject &json) {
    BaseUser::fromJson(json);
}

