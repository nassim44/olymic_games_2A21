#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDateEdit>
#include <QTabWidget>
#include "connection.h"
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>

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

void MainWindow::on_pushButton_supprimer_clicked()
{

}
