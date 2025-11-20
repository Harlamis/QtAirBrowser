#include "register_window.h"
#include "ui_register_window.h"
#include "BaseUser.h"
#include "Admin.h"
#include "User.h"
#include "ValidationException.h"
#include <QMessageBox>
#include <QString>

Register_window::Register_window(QWidget *parent)
    : QWidget(nullptr)
    , ui(new Ui::Register_window)
    , m_loginWindow(parent)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance(); //accesing database
}

Register_window::~Register_window()
{
    delete ui;
}

void Register_window::on_Register_submit_btn_clicked() {
    ui->status_label->clear();
    try {
        //collecting data
        QString name = ui->Register_username_input->text().trimmed();
        QString login = ui->Register_login_input->text().trimmed();
        QString password = ui->Register_password_input->text().trimmed();
        bool isAdmin = ui->Register_admin_checkbox->isChecked();
        //validation
        if (name.isEmpty()) throw ValidationExcpetion("Please enter username");
        if (login.isEmpty()) throw ValidationExcpetion("Please enter Login");
        if (password.isEmpty()) throw ValidationExcpetion("Please enter a password");
        if (password.length() < 8) throw ValidationExcpetion("Password must be at least 8 characters long");
        //making sure that there is no dublicate user in DB
        if (m_db->findUser(login)) throw ValidationExcpetion("User with this login already exists");
        BaseUser* newUser = 0;
        if (isAdmin) {
            newUser = new Admin(name,login,password);
        } else {
            newUser = new User(name,login,password);
        }
        //Adding to the DB
        if (m_db->addUser(newUser)) {
            QMessageBox::information(this, "Success", "Account created successfully");
            //clearing fields
            ui->Register_login_input->clear();
            ui->Register_password_input->clear();
            ui->Register_username_input->clear();
            ui->Register_admin_checkbox->setChecked(false);
            //hiding this window, return to loginscreen
            this->hide();
            if (m_loginWindow) m_loginWindow->show();
        } else {
            delete newUser;
            throw ValidationExcpetion("Failed to create user for unknown reason");
        }
    } catch (ValidationExcpetion &e) {
        ui->status_label->setText(e.getMessage());
    }
}

void Register_window::on_Register_back_btn_clicked() {
    ui->status_label->clear();
    this->hide();
    if (m_loginWindow) m_loginWindow->show();
}
