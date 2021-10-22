#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPixmap pix("C:/Users/Admin/Downloads/background.jpg");
      //  ui->background->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}
