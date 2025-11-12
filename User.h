#ifndef USER_H
#define USER_H
#include <qstring.h>

#endif // USER_H

class BaseUser {
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
};

// class User {
//     QString login;
//     QString password;
// public:
//     QString GetLogin();
//     QString GetPsswd();

// };
