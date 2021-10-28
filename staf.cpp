#include "staf.h"
#include "ui_staf.h"

Staf::Staf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Staf)
{
    ui->setupUi(this);
}

Staf::~Staf()
{
    delete ui;
}

