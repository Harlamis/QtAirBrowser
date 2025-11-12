#ifndef USER_H
#define USER_H
#include "BaseUser.h"
#endif // USER_H

class User : public BaseUser {
public:
    virtual UserRole GetRole() override {return UserRole::User;}
};
