#include "deledgeform.h"
#include "ui_deledgeform.h"
#include <QString>
#include <QMessageBox>

DelEdgeForm::DelEdgeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelEdgeForm)
{
    ui->setupUi(this);
}

DelEdgeForm::~DelEdgeForm()
{
    delete ui;
}

void DelEdgeForm::check_max()
{
}
void DelEdgeForm::on_button_clicked()
{

    if (((ui->spin_source->text()).toInt() <= 0) || ((ui->spin_target->text()).toInt() > 6) || (ui->spin_source->text() ==ui->spin_target->text()))
    { QMessageBox::StandardButton reply = QMessageBox::warning(this,"ERROR","Номер узла не может быть больше или меньше кол-ва структур или равен сам себе");
     }
    else {
    isSaved = true;
    source = (ui->spin_source->text()).toInt();
    target = (ui->spin_target->text()).toInt();
    close();
    }

}
