#ifndef USER_H
#define USER_H

#include "BaseUser.h"

class User : public BaseUser {
public:
    virtual ~User() {}
    virtual UserRole GetRole() override;
};

#endif // USER_H
