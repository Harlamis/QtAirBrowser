#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QWidget>

namespace Ui {
class Register_window;
}

class Register_window : public QWidget
{
    Q_OBJECT

public:
    explicit Register_window(QWidget *parent = nullptr);
    ~Register_window();

private:
    Ui::Register_window *ui;
};

#endif // REGISTER_WINDOW_H
