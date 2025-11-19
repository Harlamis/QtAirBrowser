#ifndef ADMIN_DASHBOARD_H
#define ADMIN_DASHBOARD_H

#include "DatabaseManager.h"
#include <QMainWindow>

namespace ui {
class AdminDashboard;
}

class AdminDashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

private slots:
    void on_btn_add_designer_clicked();
    void on_btn_remove_designer_clicked();
    void on_btn_delete_user_clicked();
    void on_btn_refresh_clicked();
    void on_btn_logout_clicked();
    void on_btn_help_clicked();
    void on_search_input_textChanged(const QString &arg1);
    void on_table_designers_cellDoubleClicked();
private:
    ui::AdminDashboard *ui;
    DatabaseManager* m_db;
    void refreshDesignersTable();
    void refreshUsersTable();
};

#endif // ADMIN_DASHBOARD_H
