#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register_window.h"
#include "BaseUser.h"
#include <QMessageBox>
#include "ValidationException.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance(); //creating database instance
    try {
        if (!m_db->loadFromFile()) throw ValidationException("Failed to load database file!");
    }
    catch (ValidationException &e) {
         ui->status_label->setText(e.getMessage());
    }

    //register window init on program launch
}

MainWindow::~MainWindow()
{
    m_db->saveToFile(); //save on program closing
    delete ui;
}

void MainWindow::on_Login_register_btn_clicked()
{
    m_registerWindow = new Register_window(this);
    m_registerWindow->show();
    // this->hide();
}

void MainWindow::on_Login_submit_btn_clicked()
{
    try {
        //Collect data
        QString username = ui->Login_username_input->text().trimmed(); //trim to get rid of spaces
        QString password = ui->Login_password_input->text();
        if (username.isEmpty()) throw ValidationException("Please, enter your username");
        if (password.isEmpty()) throw ValidationException("Please, enter your password");
        //attempting to login...
        BaseUser* user = m_db->login(username,password);
        if (user == nullptr) {
            throw ValidationException("Invalid login or password");
        }
        ui->Login_password_input->clear();
        this->hide();
        QString role = user->GetRole();
        if (m_dashboard == nullptr) {
                m_dashboard = new Dashboard(user,this);
        }
        m_dashboard->show();
    }
    catch (const ValidationException &e) {
        ui->status_label->setText(e.getMessage());
    }

}

