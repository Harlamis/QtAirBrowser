#include "AircraftDesigner.h"
#include "AircraftProduct.h"
#include "Commercial.h"
#include "Fighter.h"
#include <QtAlgorithms>
#include <QtGlobal>

AircraftDesigner::AircraftDesigner(QString name)
    : name{name}, revenue{0}, products{} {}

AircraftDesigner::AircraftDesigner()
    : AircraftDesigner("") {}

AircraftDesigner::~AircraftDesigner() {
    qDeleteAll(products);
    products.clear();
}

QString AircraftDesigner::GetName() const {
    return name;
}

QList<AircraftProduct*> AircraftDesigner::GetProductsList() const {
    return products;
}

void AircraftDesigner::AddProduct(AircraftProduct* product) {
    if (product) {
        products.append(product);
        qDebug() << "Product added" << product->GetModelName();
        return;
    }
    qWarning("Attempted to add a null priduct.");
    return;
}

bool AircraftDesigner::RmProduct(const QString &product_name) {
    QMutableListIterator<AircraftProduct*> i(products);
    while (i.hasNext()) {
        AircraftProduct* product = i.next();
        if (product && product->GetModelName() == product_name) {
            i.remove();
            delete product;
            qDebug() << "product was released during removal from list\n";
            return true;
        }
    }
    return false;
}

void AircraftDesigner::fromJson(const QJsonObject &json) {
    name = json["name"].toString();
    revenue = json["revenue"].toDouble();

    qDeleteAll(products);
    products.clear();

    if (json.contains("products") && json["products"].isArray()) {
        QJsonArray productsArr = json["products"].toArray();

        for (const QJsonValue &val : productsArr) {
            QJsonObject productObject = val.toObject();

            QString type = productObject["type"].toString();
            AircraftProduct* newProduct = nullptr;

            if (type == "Commercial") {
                newProduct = new Commercial();
            } else if (type == "Fighter") {
                newProduct = new Fighter();
            }

            if (newProduct) {
                newProduct->fromJson(productObject);
                products.append(newProduct);
            } else {
                qWarning() << "Unknown product type encountered during loading:" << type;
            }
        }
    }
}

QJsonObject AircraftDesigner::toJson() const {
    QJsonObject designerObject;
    designerObject["name"] = name;
    designerObject["revenue"] = revenue;
    QJsonArray productsArr;
    for ( AircraftProduct* product : qAsConst(products)) {
        if (product) {
            QJsonObject productJson = product->toJson();
            productJson["type"] = product->GetType();
            productsArr.append(productJson);
        }
    }
    designerObject["products"] = productsArr;
    return designerObject;
}
