#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//QPixmap pix("C:/Users/Admin/Desktop/background.png");

MainWindow::~MainWindow()
{
    delete ui;
}
