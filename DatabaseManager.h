#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QList>
#include <QString>
#include <QJsonArray>


class BaseUser;
class AircraftDesigner;
class QJsonObject;

class DatabaseManager {
private:
    QList<BaseUser*> m_users;
    QList<AircraftDesigner*> m_designers;
    BaseUser* m_currentUser;

    static DatabaseManager* m_instance;

    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    DatabaseManager(DatabaseManager&&) = delete;
    DatabaseManager& operator=(DatabaseManager&&) = delete;

public:
    static DatabaseManager& instance();

    bool loadFromFile();
    bool saveToFile() const;

    BaseUser* login(const QString& login, const QString& password);
    void logout();
    BaseUser* getCurrentUser() const;

    bool addUser(BaseUser* user);
    bool removeUser(const QString& login);

    bool addDesigner(AircraftDesigner* designer);
    bool removeDesigner(const QString& name);

    QList<AircraftDesigner*> getDesigners() const;
    QList<BaseUser*> getUsers() const;

    AircraftDesigner* findDesigner(const QString& name) const;
    BaseUser* findUser(const QString& login) const;

private:
    void loadUsers(const QJsonArray& usersArray);
    void loadDesigners(const QJsonArray& designersArray);
};

#endif // DATABASEMANAGER_H
