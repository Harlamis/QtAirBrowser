#include "DatabaseManager.h"
#include "BaseUser.h"
#include "User.h"
#include "Admin.h"
#include "AircraftDesigner.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtAlgorithms>
#include <QtGlobal>

DatabaseManager* DatabaseManager::m_instance = nullptr;
const QString DATABASE_FILE = "database.json";

DatabaseManager& DatabaseManager::instance() {
    if (m_instance == nullptr) {
        m_instance = new DatabaseManager();
    }
    return *m_instance;
}

DatabaseManager::DatabaseManager() : m_currentUser(nullptr) {}

DatabaseManager::~DatabaseManager() {
    qDeleteAll(m_users);
    m_users.clear();
    qDeleteAll(m_designers);
    m_designers.clear();
    m_currentUser = nullptr;
}

bool DatabaseManager::LoadFromFile() {
    QFile loadFile(DATABASE_FILE);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject rootObject = loadDoc.object();

    if (rootObject.contains("users") && rootObject["users"].isArray()) {
        loadUsers(rootObject["users"].toArray());
    }
    if (rootObject.contains("designers") && rootObject["designers"].isArray()) {
        loadDesigners(rootObject["designers"].toArray());
    }

    return true;
}

void DatabaseManager::loadUsers(const QJsonArray& usersArray) {
    qDeleteAll(m_users);
    m_users.clear();

    for (const QJsonValue &val : usersArray) {
        QJsonObject userObject = val.toObject();
        QString role = userObject["_role"].toString();
        BaseUser* newUser = nullptr;

        if (role == "Admin") {
            newUser = new Admin();
        } else if (role == "User") {
            newUser = new User();
        }

        if (newUser) {
            newUser->fromJson(userObject);
            m_users.append(newUser);
        } else {
            qWarning() << "Unknown user role encountered:" << role;
        }
    }
}

void DatabaseManager::loadDesigners(const QJsonArray& designersArray) {
    qDeleteAll(m_designers);
    m_designers.clear();

    for (const QJsonValue &val : designersArray) {
        AircraftDesigner* newDesigner = new AircraftDesigner();
        newDesigner->fromJson(val.toObject());
        m_designers.append(newDesigner);
    }
}

bool DatabaseManager::SaveToFile() const {
    QFile saveFile(DATABASE_FILE);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject rootObject;
    QJsonArray usersArray;
    QJsonArray designersArray;

    for (const BaseUser* user : qAsConst(m_users)) {
        usersArray.append(user->toJson());
    }
    for (const AircraftDesigner* designer : qAsConst(m_designers)) {
        designersArray.append(designer->toJson());
    }

    rootObject["users"] = usersArray;
    rootObject["designers"] = designersArray;

    QJsonDocument saveDoc(rootObject);
    saveFile.write(saveDoc.toJson(QJsonDocument::Indented));
    saveFile.close();

    return true;
}

BaseUser* DatabaseManager::Login(const QString& login, const QString& password) {
    for (BaseUser* user : qAsConst(m_users)) {
        if (user->GetLogin() == login && user->CheckPassword(password)) {
            m_currentUser = user;
            return m_currentUser;
        }
    }
    m_currentUser = nullptr;
    return nullptr;
}

void DatabaseManager::Logout() {
    m_currentUser = nullptr;
}

BaseUser* DatabaseManager::GetCurrentUser() const {
    return m_currentUser;
}

bool DatabaseManager::AddUser(BaseUser* user) {
    if (!user || FindUser(user->GetLogin())) {
        return false;
    }
    m_users.append(user);
    return true;
}

bool DatabaseManager::RemoveUser(const QString& login) {
    QMutableListIterator<BaseUser*> i(m_users);
    while (i.hasNext()) {
        BaseUser* user = i.next();
        if (user && user->GetLogin() == login) {
            if (user == m_currentUser) {
                Logout();
            }
            i.remove();
            delete user;
            return true;
        }
    }
    return false;
}

bool DatabaseManager::AddDesigner(AircraftDesigner* designer) {
    if (!designer || FindDesigner(designer->GetName())) {
        return false;
    }
    m_designers.append(designer);
    return true;
}

bool DatabaseManager::RemoveDesigner(const QString& name) {
    QMutableListIterator<AircraftDesigner*> i(m_designers);
    while (i.hasNext()) {
        AircraftDesigner* designer = i.next();
        if (designer && designer->GetName() == name) {
            i.remove();
            delete designer;
            return true;
        }
    }
    return false;
}

QList<AircraftDesigner*> DatabaseManager::GetDesigners() const {
    return m_designers;
}

QList<BaseUser*> DatabaseManager::GetUsers() const {
    return m_users;
}

AircraftDesigner* DatabaseManager::FindDesigner(const QString& name) const {
    for (AircraftDesigner* designer : qAsConst(m_designers)) {
        if (designer->GetName() == name) {
            return designer;
        }
    }
    return nullptr;
}

BaseUser* DatabaseManager::FindUser(const QString& login) const {
    for (BaseUser* user : qAsConst(m_users)) {
        if (user->GetLogin() == login) {
            return user;
        }
    }
    return nullptr;
}
