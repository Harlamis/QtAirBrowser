#include "admin_dashboard.h"
#include "ui_admin_dashboard.h"
#include "AircraftDesigner.h"
#include "BaseUser.h"
#include "productmanager_window.h"
#include <QInputDialog>
#include <QMessageBox>

AdminDashboard::AdminDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminDashboard)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance();

    refreshDesignersTable();
    refreshUsersTable();
}

AdminDashboard::~AdminDashboard()
{
    delete ui;
}

void AdminDashboard::refreshDesignersTable()
{
    ui->table_designers->setRowCount(0);

    ui->table_designers->setSortingEnabled(false);

    QList<AircraftDesigner*> designers = m_db->getDesigners();

    for (AircraftDesigner* d : designers) {
        int row = ui->table_designers->rowCount();
        ui->table_designers->insertRow(row);
        ui->table_designers->setItem(row, 0, new QTableWidgetItem(d->GetName()));
        QTableWidgetItem* revenueItem = new QTableWidgetItem();
        revenueItem->setData(Qt::DisplayRole, d->RecalculateRevenue());
        ui->table_designers->setItem(row, 1, revenueItem);
        QTableWidgetItem* countItem = new QTableWidgetItem();
        countItem->setData(Qt::DisplayRole, d->GetProductsList().size());
        ui->table_designers->setItem(row, 2, countItem);
    }
    ui->table_designers->setSortingEnabled(true);
}

void AdminDashboard::refreshUsersTable()
{
    ui->table_users->setRowCount(0);
    QList<BaseUser*> users = m_db->getUsers();

    for (BaseUser* u : users) {
        int row = ui->table_users->rowCount();
        ui->table_users->insertRow(row);
        ui->table_users->setItem(row, 0, new QTableWidgetItem(u->GetLogin()));
        ui->table_users->setItem(row, 1, new QTableWidgetItem(u->GetName()));
        ui->table_users->setItem(row, 2, new QTableWidgetItem(u->GetRole()));
    }
}

void AdminDashboard::on_btn_add_designer_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Designer",
                                         "Designer Name:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !name.isEmpty()) {
        AircraftDesigner* newDesigner = new AircraftDesigner(name);
        if (m_db->addDesigner(newDesigner)) {
            m_db->saveToFile();
            refreshDesignersTable();
            QMessageBox::information(this, "Success", "Designer added successfully.");
        } else {
            delete newDesigner;
            QMessageBox::warning(this, "Error", "Designer already exists.");
        }
    }
}

void AdminDashboard::on_btn_remove_designer_clicked()
{
    int currentRow = ui->table_designers->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Selection", "Please select a designer to delete.");
        return;
    }

    QString name = ui->table_designers->item(currentRow, 0)->text();

    auto reply = QMessageBox::question(this, "Confirm Delete",
                                       "Delete designer '" + name + "' and all their products?",
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_db->removeDesigner(name)) {
            m_db->saveToFile();
            refreshDesignersTable();
        }
    }
}

void AdminDashboard::on_btn_delete_user_clicked()
{
    int currentRow = ui->table_users->currentRow();
    if (currentRow < 0) return;

    QString login = ui->table_users->item(currentRow, 0)->text();
    if (login == m_db->getCurrentUser()->GetLogin()) {
        QMessageBox::warning(this, "Error", "You cannot delete yourself!");
        return;
    }

    if (m_db->removeUser(login)) {
        m_db->saveToFile();
        refreshUsersTable();
    }
}

void AdminDashboard::on_search_input_textChanged(const QString &arg1)
{
    QString filter = arg1.toLower();

    for (int i = 0; i < ui->table_designers->rowCount(); ++i) {
        bool match = false;
        // at index 0 we have "name" field
        QTableWidgetItem *item = ui->table_designers->item(i, 0);
        if (item && item->text().toLower().contains(filter)) {
            match = true;
        }
        ui->table_designers->setRowHidden(i, !match);
    }
}

void AdminDashboard::on_btn_help_clicked()
{
    //lmao why not use html
    QString helpText =
        "<h3>Admin Dashboard Manual</h3>"
        "<ul>"
        "<li><b>Add Designer:</b> Click the green button to create a new aircraft company.</li>"
        "<li><b>Edit Designer:</b> Double-click on a designer row to edit details or manage products.</li>"
        "<li><b>Delete:</b> Select a row and click 'Delete Selected'.</li>"
        "<li><b>Search:</b> Type in the search bar to filter the list by name.</li>"
        "<li><b>Sorting:</b> Click on column headers to sort data.</li>"
        "</ul>";

    QMessageBox::about(this, "User Manual", helpText);
}

void AdminDashboard::on_table_designers_cellDoubleClicked(int row, int column) {
    QTableWidgetItem* item = ui->table_designers->item(row, 0);
    if (!item) return;

    QString designerName = item->text();

    AircraftDesigner* designer = m_db->findDesigner(designerName);

    if (designer) {
        ProductManagerWindow managerWindow(designer, this);
        managerWindow.exec();
        refreshDesignersTable();
    } else {
        QMessageBox::warning(this, "Error", "Designer not found in database!");
    }
}

void AdminDashboard::on_btn_refresh_clicked()
{
    refreshDesignersTable();
    refreshUsersTable();
}

void AdminDashboard::on_btn_logout_clicked()
{
    m_db->logout();
    this->close();
    if (this->parentWidget()) {
        this->parentWidget()->show();
    }
}
