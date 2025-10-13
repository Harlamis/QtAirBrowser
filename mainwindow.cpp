#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "register_window.h"
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QFIle>
#include <QPair>
#include <QDebug>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Login_register_btn_clicked()
{
    Register_window* register_window = new Register_window();
    register_window->setAttribute(Qt::WA_DeleteOnClose);
    register_window->setWindowModality(Qt::ApplicationModal);
    register_window->show();
}
const QString &ADMINPASSWORD() {
    static const QString pw = QStringLiteral("Cplusplus");
    return pw;
}

void MainWindow::on_Login_submit_btn_clicked()
{
    try {
        QString path = QCoreApplication::applicationDirPath() + "/../../rcs/users.txt";
        qDebug() << "Trying to open:" << path;
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error(QString("Cannot open file for reading").toStdString());
        }
        QTextStream in(&file);
        while (!file.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty() || !line.contains(':')) {
                continue;
            }
            QStringList parts = line.split(':');
            try {
                if (parts.size() < 2) {
                    throw std::invalid_argument(("Error reading line: " + line + " Expected format is: username:password").toStdString());
                }
                QString input_login = this->ui->Login_username_input->text();
                QString input_password = this->ui->Login_password_input->text();
                QString login = parts.at(0).trimmed();
                QString password = parts.mid(1).join(':').trimmed();
                if (input_login == login) {
                    if (input_password == password) {
                        // To the next window
                        QMessageBox::warning(this, "Warning", "Succes!");
                        return;
                    }
                    else {
                        QMessageBox::warning(this, "Warning", "Invalid password!");
                        return;
                    }
                }
                else {
                    QMessageBox::warning(this, "Warning", "User not found!");
                    return;
                }
            }

            catch (const std::invalid_argument &e) {
                QMessageBox::critical(this, "Format error", e.what());
            }
        }
    }
    catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Cannot read file", e.what());
    }
}

