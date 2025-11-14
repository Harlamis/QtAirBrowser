#ifndef AIRCRAFTDESIGNER_H
#define AIRCRAFTDESIGNER_H
#include <Qlist>
#include <QMutableListIterator>
#include "AircraftProduct.h"
#endif // AIRCRAFTDESIGNER_H

class AircraftDesigner : public ISerializable {
    QString name;
    QList<AircraftProduct*> products;
    double revenue = 0;
public:
    AircraftDesigner(QString name)
        : name{name}, revenue{0}, products{} {};
    AircraftDesigner()
        : AircraftDesigner("") {};

    QString GetName() {
        return name;
    }

    QList<AircraftProduct*> GetProductsList() {
        return products;
    }

    void AddProduct(AircraftProduct* product) {
        if (product) {
            products.append(product);
            qDebug() << "Product added" << product->GetModelName();
            return;
        }
        qWarning("Attempted to add a null priduct.");
        return;
    }

    bool RmProduct(const QString &product_name) {
        QMutableListIterator<AircraftProduct*> i(products);
        while (i.hasNext()) {
            AircraftProduct* product = i.next();
            if (product && product->GetModelName() == product_name) {
                i.remove();
            }
            delete product;
            qDebug() << "product was released during removal from list\n";
            return true;
        }
        return false;
    }
};
