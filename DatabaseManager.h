#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QList>
#include <QString>
#include <QJsonArray>

class BaseUser;
class AircraftDesigner;
class QJsonObject;

/// @brief Singleton class for managing data persistence and application state.
/// Handles loading/saving users and designers to a JSON file.
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
    /// @brief Returns the singleton instance.
    static DatabaseManager& instance();

    /// @brief Loads data from JSON file.
    /// @return True on success.
    bool loadFromFile();

    /// @brief Saves data to JSON file.
    /// @return True on success.
    bool saveToFile() const;

    /// @brief Logs in a user.
    /// @param login User login.
    /// @param password User password.
    /// @return Pointer to user or nullptr.
    BaseUser* login(const QString& login, const QString& password);

    /// @brief Logs out the current user.
    void logout();

    /// @brief Gets the currently logged-in user.
    BaseUser* getCurrentUser() const;

    /// @brief Adds a new user.
    /// @param user Pointer to user.
    /// @return True if added.
    bool addUser(BaseUser* user);

    /// @brief Removes a user by login.
    bool removeUser(const QString& login);

    /// @brief Adds a new designer.
    bool addDesigner(AircraftDesigner* designer);

    /// @brief Removes a designer by name.
    bool removeDesigner(const QString& name);

    /// @brief Gets all designers.
    QList<AircraftDesigner*> getDesigners() const;

    /// @brief Gets all users.
    QList<BaseUser*> getUsers() const;

    /// @brief Finds a designer by name.
    AircraftDesigner* findDesigner(const QString& name) const;

    /// @brief Finds a user by login.
    BaseUser* findUser(const QString& login) const;

private:
    void loadUsers(const QJsonArray& usersArray);
    void loadDesigners(const QJsonArray& designersArray);
};

#endif // DATABASEMANAGER_H
