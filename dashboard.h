#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "DatabaseManager.h"
#include <QMainWindow>

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void on_btn_add_designer_clicked();
    void on_btn_remove_designer_clicked();
    void on_btn_delete_user_clicked();
    void on_btn_refresh_clicked();
    void on_btn_logout_clicked();
    void on_btn_help_clicked();
    void on_search_input_textChanged(const QString &arg1);
    void on_table_designers_cellDoubleClicked(int row, int column);
private:
    Ui::Dashboard *ui;
    DatabaseManager* m_db;
    void refreshDesignersTable();
    void refreshUsersTable();
};

#endif // DASHBOARD_H
