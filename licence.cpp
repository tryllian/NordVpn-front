#include "licence.h"
#include "ui_licence.h"

Licence::Licence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Licence)
{
    ui->setupUi(this);
}

Licence::~Licence()
{
    delete ui;
}
