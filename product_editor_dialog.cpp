#include "product_editor_dialog.h"
#include "ui_product_editor_dialog.h"

#include "Commercial.h"
#include "Fighter.h"
#include <QMessageBox>
#include <QPushButton>

ProductEditorDialog::ProductEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductEditorDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(ui->combo_type->currentIndex());
    ui->buttonBox->button(QDialogButtonBox::Save)->setAutoDefault(true);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &ProductEditorDialog::on_buttonBox_accepted);


    disconnect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
}

ProductEditorDialog::~ProductEditorDialog()
{
    delete ui;
}

void ProductEditorDialog::on_combo_type_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void ProductEditorDialog::on_buttonBox_accepted()
{
    QString model = ui->inp_model->text().trimmed();
    if (model.isEmpty()) {
        QMessageBox::warning(this, "Error", "Model name cannot be empty.");
        return;
    }

    QString type = ui->combo_type->currentText();

    if (type == "Commercial") {
        Commercial* c = new Commercial();

        c->SetNumberOfDecks(ui->comm_decks->value());
        c->SetNumberOfPilots(ui->comm_pilots->value());
        c->SetPassengerCapacity(ui->comm_passengers->value());
        c->SetLuggageCapacity(ui->comm_luggage->value());

        m_product = c;
    }
    else if (type == "Fighter") {
        Fighter* f = new Fighter();
        f->SetStealthRange(ui->fight_stealth->value());
        f->SetAmmoCapacity(ui->fight_ammo->value());
        f->SetMaxFlightHeight(ui->fight_height->value());

        m_product = f;
    }

    if (m_product) {
        m_product->SetModelName(model);
        m_product->SetPrice(ui->inp_price->value());
        m_product->SetMaxSpeed(ui->inp_speed->value());
        m_product->SetSoldUnits(0);
        accept();
    }
}

AircraftProduct* ProductEditorDialog::GetCreatedProduct() const {
    return m_product;
}
