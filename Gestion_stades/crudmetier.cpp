#include "crudmetier.h"
#include "ui_crudmetier.h"
//ici les crud et metier
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
