#include "mail.h"
#include "ui_mail.h"

Mail::Mail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mail)
{
    ui->setupUi(this);
}

Mail::~Mail()
{
    delete ui;
}
