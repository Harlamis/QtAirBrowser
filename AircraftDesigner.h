#ifndef AIRCRAFTDESIGNER_H
#define AIRCRAFTDESIGNER_H

#include <QList>
#include <QMutableListIterator>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include "ISerializable.h"

class AircraftProduct; //forvard declaration

class AircraftDesigner : public ISerializable {
    QString name;
    QList<AircraftProduct*> products;
    double revenue = 0;
public:
    AircraftDesigner(QString name);
    AircraftDesigner();
    virtual ~AircraftDesigner();

    QString GetName() const;
    QList<AircraftProduct*> GetProductsList() const;

    void AddProduct(AircraftProduct* product);
    bool RmProduct(const QString &product_name);

    virtual void fromJson(const QJsonObject &json) override;
    virtual QJsonObject toJson() const override;
};

#endif // AIRCRAFTDESIGNER_H
