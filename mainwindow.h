#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DatabaseManager.h"
#include "register_window.h"
#include "dashboard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Login_register_btn_clicked();

    void on_Login_submit_btn_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager* m_db; //database manager singleton
    // future windows will be here
    Register_window* m_registerWindow;
    AdminDashboard* m_adminDashboard = nullptr;

};
#endif // MAINWINDOW_H
