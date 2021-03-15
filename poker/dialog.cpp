#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QString str) :
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setText(str);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    emit this->again();//传出信号
}

void Dialog::on_pushButton_2_clicked()
{
    emit this->back();
}
