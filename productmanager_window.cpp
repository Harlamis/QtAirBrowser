#include "productmanager_window.h"
#include "ui_productmanager_window.h"
#include "AircraftDesigner.h"
#include "Commercial.h"
#include <QInputDialog>
#include <QMessageBox>
#include "product_editor_dialog.h"


ProductManagerWindow::ProductManagerWindow(AircraftDesigner* designer,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductManagerWindow)
    , m_designer(designer)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance();
    this->setWindowTitle("Manage products for " + m_designer->GetName());
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
        speedItem->setData(Qt::DisplayRole, p->GetMax_speed());
        ui->table_products->setItem(row, 2, speedItem);

        // Price
        QTableWidgetItem* priceItem = new QTableWidgetItem();
        priceItem->setData(Qt::DisplayRole, p->GetPrice());
        ui->table_products->setItem(row, 3, priceItem);

        // Sold
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

    for (int i = 0; i < ui->table_products->rowCount(); ++i) {
        bool showRow = true;
        QString name = ui->table_products->item(i, 0)->text().toLower();
        if (!name.contains(nameFilter)) showRow = false;
        QString type = ui->table_products->item(i, 1)->text();
        if (typeFilter != "All Types" && type != typeFilter) showRow = false;
        double speed = ui->table_products->item(i, 2)->data(Qt::DisplayRole).toDouble();
        if (speed < minSpeed) showRow = false;
        ui->table_products->setRowHidden(i, !showRow);
    }
}

void ProductManagerWindow::on_filter_name_textChanged(const QString &arg1) { applyFilters(); }
void ProductManagerWindow::on_filter_type_currentTextChanged(const QString &arg1) { applyFilters(); }
void ProductManagerWindow::on_filter_min_speed_valueChanged(int &arg1) { applyFilters(); }

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

