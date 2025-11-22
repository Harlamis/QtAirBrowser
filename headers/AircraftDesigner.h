#ifndef AIRCRAFTDESIGNER_H
#define AIRCRAFTDESIGNER_H

#include <QList>
#include <QMutableListIterator>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include "ISerializable.h"

class AircraftProduct;

/// @brief Represents an aircraft design company.
/// Holds a list of products and tracks total revenue.
class AircraftDesigner : public ISerializable {
    QString name;
    QList<AircraftProduct*> products;
    double revenue = 0;
public:
    AircraftDesigner(QString name);
    AircraftDesigner();
    virtual ~AircraftDesigner();

    /// @brief Gets the designer's name.
    /// @return The name string.
    QString GetName() const;

    /// @brief Gets the list of products.
    /// @return A QList of pointers to AircraftProduct.
    QList<AircraftProduct*> GetProductsList() const;

    /// @brief Adds a product to the designer's list.
    /// @param product Pointer to the product. Ownership is transferred.
    void AddProduct(AircraftProduct* product);

    /// @brief Removes a product by name.
    /// @param product_name The name of the product to remove.
    /// @return True if removed, false otherwise.
    bool RmProduct(const QString &product_name);

    /// @brief Recalculates total revenue from all products.
    /// @return The total revenue sum.
    double RecalculateRevenue();

    virtual void fromJson(const QJsonObject &json) override;
    virtual QJsonObject toJson() const override;
};

#endif // AIRCRAFTDESIGNER_H
