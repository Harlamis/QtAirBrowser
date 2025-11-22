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
    bool LoadFromFile();

    /// @brief Saves data to JSON file.
    /// @return True on success.
    bool SaveToFile() const;

    /// @brief Logs in a user.
    /// @param Login User Login.
    /// @param password User password.
    /// @return Pointer to user or nullptr.
    BaseUser* Login(const QString& login, const QString& password);

    /// @brief Logs out the current user.
    void Logout();

    /// @brief Gets the currently logged-in user.
    BaseUser* GetCurrentUser() const;

    /// @brief Adds a new user.
    /// @param user Pointer to user.
    /// @return True if added.
    bool AddUser(BaseUser* user);

    /// @brief Removes a user by login.
    bool RemoveUser(const QString& login);

    /// @brief Adds a new designer.
    bool AddDesigner(AircraftDesigner* designer);

    /// @brief Removes a designer by name.
    bool RemoveDesigner(const QString& name);

    /// @brief Gets all designers.
    QList<AircraftDesigner*> GetDesigners() const;

    /// @brief Gets all users.
    QList<BaseUser*> GetUsers() const;

    /// @brief Finds a designer by name.
    AircraftDesigner* FindDesigner(const QString& name) const;

    /// @brief Finds a user by login.
    BaseUser* FindUser(const QString& login) const;

private:
    void loadUsers(const QJsonArray& usersArray);
    void loadDesigners(const QJsonArray& designersArray);
};

#endif // DATABASEMANAGER_H
