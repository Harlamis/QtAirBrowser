#include "Admin.h"
#include <QJsonObject>
#include <QDebug>
#include <utility>

Admin::Admin() : BaseUser() {}

Admin::Admin(QString new_name, QString new_login, QString new_password)
    : BaseUser(new_name, new_login, new_password) {}

Admin::~Admin() {}

Admin::Admin(const Admin& other) : BaseUser(other) {}

Admin& Admin::operator=(const Admin& other) {
    if (this != &other) {
        BaseUser::operator=(other);
    }
    return *this;
}

Admin::Admin(Admin&& other) noexcept : BaseUser(std::move(other)) {}

Admin& Admin::operator=(Admin&& other) noexcept {
    if (this != &other) {
        BaseUser::operator=(std::move(other));
    }
    return *this;
}

QString Admin::GetRole() const {
    return "Admin";
}

QJsonObject Admin::toJson() const {
    QJsonObject json = BaseUser::toJson();
    json["_role"] = GetRole();
    return json;
}

void Admin::fromJson(const QJsonObject &json) {
    BaseUser::fromJson(json);
}
