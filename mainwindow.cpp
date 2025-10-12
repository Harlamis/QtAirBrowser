#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "register_window.h"

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
