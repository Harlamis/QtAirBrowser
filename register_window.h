#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QWidget>
#include "DatabaseManager.h"

namespace Ui {
class Register_window;
}

class Register_window : public QWidget
{
    Q_OBJECT

public:
    explicit Register_window(QWidget *parent = nullptr);
    ~Register_window();

private slots:
    void on_Register_submit_btn_clicked();
    void on_Register_back_btn_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Register_window *ui;
    QWidget* m_loginWindow; //we keep this not to loose main window when pressing back btn
    DatabaseManager* m_db;
};

#endif // REGISTER_WINDOW_H
