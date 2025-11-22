#include "dashboard.h"
#include "ui_dashboard.h"
#include "AircraftDesigner.h"
#include "BaseUser.h"
#include "productmanager_window.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>
#include <QCloseEvent>

Dashboard::Dashboard(BaseUser* user,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard),
    m_currentUser(user)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance();

    refreshDesignersTable();
    refreshUsersTable();
    setupPermissions();
    refreshDesignersTable();
    if (m_currentUser->GetName() == "Admin") {
        refreshUsersTable();
    }
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::closeEvent(QCloseEvent *event) {
    if (this->parentWidget() && !this->parentWidget()->isVisible()){
        QApplication::exit(0);
    }
    event->accept();
}

void Dashboard::setupPermissions() {
    QString role = m_currentUser->GetRole();
    this->setWindowTitle("Manage AirBrowser, role: " + role);
    if (role != "Admin") {
        int userTabIndex = ui->tabWidget->indexOf(ui->tab_users);
        if (userTabIndex != -1) {
            ui->tabWidget->removeTab(userTabIndex);
        }
    }
}

void Dashboard::refreshDesignersTable()
{
    ui->table_designers->setRowCount(0);

    ui->table_designers->setSortingEnabled(false);

    QList<AircraftDesigner*> designers = m_db->GetDesigners();

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

void Dashboard::refreshUsersTable()
{
    ui->table_users->setRowCount(0);
    QList<BaseUser*> users = m_db->GetUsers();

    for (BaseUser* u : users) {
        int row = ui->table_users->rowCount();
        ui->table_users->insertRow(row);
        ui->table_users->setItem(row, 0, new QTableWidgetItem(u->GetLogin()));
        ui->table_users->setItem(row, 1, new QTableWidgetItem(u->GetName()));
        ui->table_users->setItem(row, 2, new QTableWidgetItem(u->GetRole()));
    }
}

void Dashboard::on_btn_add_designer_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Designer",
                                         "Designer Name:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !name.isEmpty()) {
        AircraftDesigner* newDesigner = new AircraftDesigner(name);
        if (m_db->AddDesigner(newDesigner)) {
            m_db->SaveToFile();
            refreshDesignersTable();
            QMessageBox::information(this, "Success", "Designer added successfully.");
        } else {
            delete newDesigner;
            QMessageBox::warning(this, "Error", "Designer already exists.");
        }
    }
}

void Dashboard::on_btn_remove_designer_clicked()
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
        if (m_db->RemoveDesigner(name)) {
            m_db->SaveToFile();
            refreshDesignersTable();
        }
    }
}

void Dashboard::on_btn_delete_user_clicked()
{
    int currentRow = ui->table_users->currentRow();
    if (currentRow < 0) return;

    QString login = ui->table_users->item(currentRow, 0)->text();
    if (login == m_db->GetCurrentUser()->GetLogin()) {
        QMessageBox::warning(this, "Error", "You cannot delete yourself!");
        return;
    }

    if (m_db->RemoveUser(login)) {
        m_db->SaveToFile();
        refreshUsersTable();
    }
}

void Dashboard::on_search_input_textChanged(const QString &arg1)
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

void Dashboard::on_btn_help_clicked()
{
    //lmao why not use html
    QString helpText =
        "<h3>Dashboard Manual</h3>"
        "<ul>"
        "<li><b>Add Designer:</b> Click the green button to create a new aircraft company.</li>"
        "<li><b>Edit Designer:</b> Double-click on a designer row to edit details or manage products.</li>"
        "<li><b>Delete:</b> Select a row and click 'Delete Selected'.</li>"
        "<li><b>Search:</b> Type in the search bar to filter the list by name.</li>"
        "<li><b>Sorting:</b> Click on column headers to sort data.</li>"
        "</ul>";

    QMessageBox::about(this, "User Manual", helpText);
}

void Dashboard::on_table_designers_cellDoubleClicked(int row, int column) {
    QTableWidgetItem* item = ui->table_designers->item(row, 0);
    if (!item) return;

    QString designerName = item->text();

    AircraftDesigner* designer = m_db->FindDesigner(designerName);

    if (designer) {
        ProductManagerWindow managerWindow(designer, this);
        managerWindow.exec();
        refreshDesignersTable();
    } else {
        QMessageBox::warning(this, "Error", "Designer not found in database!");
    }
}

void Dashboard::on_btn_refresh_clicked()
{
    refreshDesignersTable();
    refreshUsersTable();
}

void Dashboard::on_btn_logout_clicked()
{
    m_db->Logout();
    if (this->parentWidget()) {
        this->parentWidget()->show();
    }
    this->close();
}

