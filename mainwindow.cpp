#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "register_window.h"
#include "BaseUser.h"
#include "ValidationException.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_db = &DatabaseManager::instance(); //creating database instance
    try {
        if (!m_db->loadFromFile()) throw ValidationExcpetion("Failed to load database file!");
    }
    catch (ValidationExcpetion &e) {
         ui->status_label->setText(e.getMessage());
    }

    //register window init on program launch
    m_registerWindow = new Register_window(this);
}

MainWindow::~MainWindow()
{
    m_db->saveToFile(); //save on program closing
    delete ui;
}

void MainWindow::on_Login_register_btn_clicked()
{
    m_registerWindow->show();
    this->hide();
}

void MainWindow::on_Login_submit_btn_clicked()
{
    try {
        //Collect data
        QString username = ui->Login_username_input->text().trimmed(); //trim to get rid of spaces
        QString password = ui->Login_password_input->text();
        if (username.isEmpty()) throw ValidationExcpetion("Please, enter your username");
        if (password.isEmpty()) throw ValidationExcpetion("Please, enter your password");

    }
    catch (const ValidationExcpetion &e) {
        ui->status_label->setText(e.getMessage());
    }

}

