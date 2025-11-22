#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QJsonObject>

/// @brief Interface for objects that can be serialized to JSON.
/// Any class that needs to be saved to the database must implement this interface.
class ISerializable {
public:
    virtual ~ISerializable() {}

    /// @brief Converts the object's state to a JSON object.
    /// @return A QJsonObject representing the object.
    virtual QJsonObject toJson() const = 0;

    /// @brief Populates the object's state from a JSON object.
    /// @param json The JSON object containing the data.
    virtual void fromJson(const QJsonObject &json) = 0;
};

#endif // ISERIALIZABLE_H
