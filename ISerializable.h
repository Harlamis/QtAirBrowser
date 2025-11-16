#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QJsonObject>

class ISerializable {
public:
    virtual ~ISerializable() {}
    virtual QJsonObject toJson() const = 0;
    virtual void fromJson(const QJsonObject &json) = 0;
};

#endif // ISERIALIZABLE_H
