#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDateEdit>
#include <QTabWidget>
#include "connection.h"
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include<QQuickItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget1->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
  ui->quickWidget1->show();
  auto obj =ui->quickWidget1->rootObject();
  connect(this,SIGNAL(setCenter(Qvariant,Qvariant)),obj,SLOT(setCenter(Qvariant,Qvariant)));
  emit setCenter(25.000,50.000);
}
//QPixmap pix("C:/Users/Admin/Desktop/background.png");

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_supprimer_clicked()
{

}
