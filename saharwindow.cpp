#include "saharwindow.h"
#include "ui_saharwindow.h"

saharwindow::saharwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::saharwindow)
{
    ui->setupUi(this);
}

saharwindow::~saharwindow()
{
    delete ui;
}

