#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#endif // ISERIALIZABLE_H
#include <QJsonObject>

class ISerializable {
    virtual QJsonObject toJson() = 0;
    virtual void formJson(const QJsonObject &json) = 0;
};
