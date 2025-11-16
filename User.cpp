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
    qDeleteAll(favourites);
    favourites.clear();
}

User::User(const User& other) : BaseUser(other) {
    for (AircraftDesigner* designer : other.favourites) {
        favourites.append(new AircraftDesigner(*designer));
    }
}

User& User::operator=(const User& other) {
    if (this == &other) {
        return *this;
    }
    BaseUser::operator=(other);

    qDeleteAll(favourites);
    favourites.clear();

    for (AircraftDesigner* designer : other.favourites) {
        favourites.append(new AircraftDesigner(*designer));
    }
    return *this;
}

User::User(User&& other) noexcept
    : BaseUser(std::move(other)),
    favourites(std::move(other.favourites)) {
}

User& User::operator=(User&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    BaseUser::operator=(std::move(other));
    qDeleteAll(favourites);
    favourites = std::move(other.favourites);
    return *this;
}

QString User::GetRole() const {
    return "User";
}

QJsonObject User::toJson() const {
    QJsonObject json = BaseUser::toJson();

    QJsonArray favouritesArray;
    for (const AircraftDesigner* designer : qAsConst(favourites)) {
        favouritesArray.append(designer->toJson());
    }
    json["favourites"] = favouritesArray;
    json["_role"] = GetRole();

    return json;
}

void User::fromJson(const QJsonObject &json) {
    BaseUser::fromJson(json);

    qDeleteAll(favourites);
    favourites.clear();

    if (json.contains("favourites") && json["favourites"].isArray()) {
        QJsonArray favouritesArray = json["favourites"].toArray();
        for (const QJsonValue& val : favouritesArray) {
            AircraftDesigner* newDesigner = new AircraftDesigner();
            newDesigner->fromJson(val.toObject());
            favourites.append(newDesigner);
        }
    }
}

void User::AddFavourite(AircraftDesigner* designer) {
    if (designer) {
        favourites.append(designer);
    }
}

bool User::RemoveFavourite(const QString& designerName) {
    QMutableListIterator<AircraftDesigner*> i(favourites);
    while (i.hasNext()) {
        AircraftDesigner* designer = i.next();
        if (designer && designer->GetName() == designerName) {
            i.remove();
            delete designer;
            return true;
        }
    }
    return false;
}

QList<AircraftDesigner*> User::GetFavourites() const {
    return favourites;
}
