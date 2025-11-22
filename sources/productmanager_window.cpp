#include "productmanager_window.h"
#include "ui_productmanager_window.h"
#include "AircraftDesigner.h"
#include <QInputDialog>
#include <QMessageBox>
#include "product_editor_dialog.h"
#include "Commercial.h"
#include "Fighter.h"


ProductManagerWindow::ProductManagerWindow(AircraftDesigner* designer,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductManagerWindow)
    , m_designer(designer)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance();
    this->setWindowTitle("Manage products for " + m_designer->GetName());
    ui->btn_add->setAutoDefault(false);
    ui->btn_add->setDefault(false);
    ui->btn_delete->setAutoDefault(false);
    ui->btn_delete->setDefault(false);
    ui->btn_close->setAutoDefault(false);
    ui->btn_close->setDefault(false);
    ui->filter_name->setFocus();
    refreshTable();
}

ProductManagerWindow::~ProductManagerWindow()
{
    delete ui;
}

void ProductManagerWindow::refreshTable() {
    ui->table_products->setRowCount(0);
    ui->table_products->setSortingEnabled(false); // Вимикаємо під час оновлення

    QList<AircraftProduct*> products = m_designer->GetProductsList();

    for (AircraftProduct* p : products) {
        int row = ui->table_products->rowCount();
        ui->table_products->insertRow(row);

        // Model Name
        ui->table_products->setItem(row, 0, new QTableWidgetItem(p->GetModelName()));

        // Type
        ui->table_products->setItem(row, 1, new QTableWidgetItem(p->GetType()));

        // Speed
        QTableWidgetItem* speedItem = new QTableWidgetItem();
        double speed = p->GetMax_speed();
        speedItem->setData(Qt::DisplayRole, QString::number(speed, 'f', 2));
        speedItem->setData(Qt::EditRole, speed);
        ui->table_products->setItem(row, 2, speedItem);

        // Price
        QTableWidgetItem* priceItem = new QTableWidgetItem();
        double price = p->GetPrice();
        priceItem->setData(Qt::DisplayRole, QString::number(price, 'f', 2));
        priceItem->setData(Qt::EditRole, price);
        ui->table_products->setItem(row, 3, priceItem);

        // Sold Units
        QTableWidgetItem* soldItem = new QTableWidgetItem();
        soldItem->setData(Qt::DisplayRole, p->GetSold_units());
        ui->table_products->setItem(row, 4, soldItem);
    }

    ui->table_products->setSortingEnabled(true);
    applyFilters();
}

void ProductManagerWindow::applyFilters()
{
    QString nameFilter = ui->filter_name->text().toLower();
    QString typeFilter = ui->filter_type->currentText();
    int minSpeed = ui->filter_min_speed->value();

    // Отримуємо значення спец-фільтрів
    int minPassengers = ui->filter_passengers->value();
    double minStealth = ui->filter_stealth->value();

    // Отримуємо повний список продуктів (щоб мати доступ до об'єктів, а не лише тексту в таблиці)
    QList<AircraftProduct*> products = m_designer->GetProductsList();

    for (int i = 0; i < ui->table_products->rowCount(); ++i) {
        bool showRow = true;

        // 1. Загальні фільтри (беремо з таблиці для швидкості, або з об'єкта)
        QString name = ui->table_products->item(i, 0)->text().toLower();
        if (!name.contains(nameFilter)) showRow = false;

        QString type = ui->table_products->item(i, 1)->text();
        if (typeFilter != "All Types" && type != typeFilter) showRow = false;

        double speed = ui->table_products->item(i, 2)->data(Qt::EditRole).toDouble();
        if (speed < minSpeed) showRow = false;

        // 2. ЕКСКЛЮЗИВНІ ФІЛЬТРИ
        // Нам потрібен доступ до самого об'єкта.
        // Оскільки порядок рядків у таблиці відповідає порядку в списку products (до сортування),
        // це може бути ненадійно, якщо таблиця відсортована користувачем.
        // Тому краще знайти об'єкт за моделлю (унікальна назва).

        QString modelName = ui->table_products->item(i, 0)->text();

        // Шукаємо об'єкт у списку (це швидко для невеликих списків)
        AircraftProduct* currentObj = nullptr;
        for (auto p : products) {
            if (p->GetModelName() == modelName) {
                currentObj = p;
                break;
            }
        }

        if (currentObj && showRow) { // Якщо рядок ще не приховано попередніми фільтрами
            if (typeFilter == "Commercial") {
                // Спроба перетворити на Commercial
                Commercial* comm = dynamic_cast<Commercial*>(currentObj);
                if (comm) {
                    // Перевірка унікального поля
                    if (comm->GetPassengers_capacity() < minPassengers) showRow = false;
                }
            }
            else if (typeFilter == "Fighter") {
                // Спроба перетворити на Fighter
                Fighter* fight = dynamic_cast<Fighter*>(currentObj);
                if (fight) {
                    // Перевірка унікального поля
                    if (fight->GetStealth_range() < minStealth) showRow = false;
                }
            }
        }

        ui->table_products->setRowHidden(i, !showRow);
    }
}

// --- СЛОТИ ---

void ProductManagerWindow::on_filter_name_textChanged(const QString &) { applyFilters(); }

void ProductManagerWindow::on_filter_type_currentTextChanged(const QString &text) {
    if (text == "Commercial") {
        ui->stackedFilter->setCurrentIndex(1);
    } else if (text == "Fighter") {
        ui->stackedFilter->setCurrentIndex(2);
    } else {
        ui->stackedFilter->setCurrentIndex(0);
    }
    applyFilters();
}

void ProductManagerWindow::on_filter_min_speed_valueChanged(int &arg1) { applyFilters(); }
void ProductManagerWindow::on_filter_passengers_valueChanged(int) { applyFilters(); }
void ProductManagerWindow::on_filter_stealth_valueChanged(double) { applyFilters(); }

void ProductManagerWindow::on_btn_add_clicked()
{
    ProductEditorDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
        AircraftProduct* newProduct = dialog.getCreatedProduct();

        if (newProduct) {
            m_designer->AddProduct(newProduct);
            m_designer->RecalculateRevenue();
            m_db->saveToFile();
            refreshTable();
            QMessageBox::information(this, "Success", "Product added successfully!");
        }
    }
}
void ProductManagerWindow::on_btn_delete_clicked()
{
    int currentRow = ui->table_products->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection", "Please select a product to delete.");
        return;
    }

    QTableWidgetItem* item = ui->table_products->item(currentRow, 0);
    if (!item) return;
    QString modelName = item->text();

    auto reply = QMessageBox::question(this, "Confirm Delete",
                                       "Are you sure you want to delete product '" + modelName + "'?",
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_designer->RmProduct(modelName)) {
            m_db->saveToFile();
            refreshTable();

            QMessageBox::information(this, "Success", "Product deleted successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete product (not found).");
        }
    }
}

void ProductManagerWindow::on_btn_close_clicked()
{
    this->close();
}

