#include "register_window.h"
#include "ui_register_window.h"

Register_window::Register_window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register_window)
{
    ui->setupUi(this);
}

Register_window::~Register_window()
{
    delete ui;
}
