#ifndef PRODUCT_EDITOR_DIALOG_H
#define PRODUCT_EDITOR_DIALOG_H

#include <QDialog>
#include "AircraftProduct.h"

namespace Ui {
class ProductEditorDialog;
}

class ProductEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductEditorDialog(QWidget *parent = nullptr);
    ~ProductEditorDialog();
    AircraftProduct* getCreatedProduct() const;

private slots:
    void on_combo_type_currentIndexChanged(int index);
    void on_buttonBox_accepted();

private:
    Ui::ProductEditorDialog *ui;
    AircraftProduct* m_product = nullptr;
};

#endif // PRODUCT_EDITOR_DIALOG_H
