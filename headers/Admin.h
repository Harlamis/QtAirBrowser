#ifndef ADMIN_H
#define ADMIN_H

#include "BaseUser.h"
#include <QJsonObject>
#include <utility>

/// @brief Represents an administrator user with extended privileges.
class Admin : public BaseUser
{
public:
    Admin();
    Admin(QString new_name, QString new_login, QString new_password);

    virtual ~Admin() override;
    Admin(const Admin& other);
    Admin& operator=(const Admin& other);
    Admin(Admin&& other) noexcept;
    Admin& operator=(Admin&& other) noexcept;

    /// @brief Returns "Admin".
    virtual QString GetRole() const override;

    virtual QJsonObject toJson() const override;
    virtual void fromJson(const QJsonObject &json) override;
};

#endif // ADMIN_H
