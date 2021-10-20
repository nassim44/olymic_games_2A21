#include "crudmetier.h"
#include "ui_crudmetier.h"

crudmetier::crudmetier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crudmetier)
{
    ui->setupUi(this);
}

crudmetier::~crudmetier()
{
    delete ui;
}
