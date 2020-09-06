#include "sourse.h"
#include "ui_sourse.h"

Sourse::Sourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sourse)
{
    ui->setupUi(this);
}

Sourse::~Sourse()
{
    delete ui;
}
