#include "newedgeform.h"
#include "ui_newedgeform.h"
#include <QMessageBox>

NewEdgeForm::NewEdgeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEdgeForm)
{
    ui->setupUi(this);
}

NewEdgeForm::~NewEdgeForm()
{
    delete ui;
}

void NewEdgeForm::check_max()
{
}
void NewEdgeForm::on_button_clicked()
{
    if (((ui->spin_source->text()).toInt() <= 0) || ((ui->spin_target->text()).toInt() > 6) || (ui->spin_source->text() ==ui->spin_target->text()))
    { QMessageBox::StandardButton reply = QMessageBox::warning(this,"ERROR","Номер узла не может быть больше или меньше кол-ва структур или равен сам себе");
     }
    else {
    isSaved = true;
    source = (ui->spin_source->text()).toInt();
    target = (ui->spin_target->text()).toInt();
    weight = ui->spin_weight->value();
    close();
    }
}
