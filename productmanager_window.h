#ifndef PRODUCTMANAGER_WINDOW_H
#define PRODUCTMANAGER_WINDOW_H

#include <QWidget>
#include <QDialog>
#include "DatabaseManager.h"
#include "dashboard.h"

namespace Ui {
class ProductManagerWindow;
}

class ProductManagerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ProductManagerWindow(AircraftDesigner* designer,QWidget *parent = nullptr);
    ~ProductManagerWindow();
private slots:
    void on_btn_add_clicked();
    void on_btn_delete_clicked();
    void on_btn_close_clicked();
    void on_filter_name_textChanged(const QString &arg1);
    void on_filter_type_currentTextChanged(const QString &arg1);
    void on_filter_min_speed_valueChanged(int &arg1);
private:
    Ui::ProductManagerWindow *ui;
    AircraftDesigner* m_designer;
    DatabaseManager* m_db;
    Dashboard* m_adminDashboard;
    void refreshTable();
    void applyFilters();
};

#endif // PRODUCTMANAGER_WINDOW_H
