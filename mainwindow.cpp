#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spectateurs.h"
#include "statistique.h"
#include <QApplication>
#include <QMessageBox>
#include<QCameraImageCapture>
#include<QCamera>
#include<QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QCameraInfo>
#include<QFileDialog>
#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QFile>
#include <QSortFilterProxyModel>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>

#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextStream>
#include<QWidget>
#include <QtSvg/QSvgRenderer>
#include<QDirModel>
#include "qrcode.h"


using qrcodegen::QrCode;
using qrcodegen::QrSegment;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mCamera = new QCamera(this);
        mCameraViewfinder = new QCameraViewfinder(this);
        mCameraImageCapture = new QCameraImageCapture(mCamera, this);


        m = new QVBoxLayout;
        mOpcionesMenu =new QMenu("Option", this);
        mEncenderAction = new QAction("ouvrir camera",this);
        mApagarAction = new QAction("voir photo",this);
        mCapturarAction =new QAction("enregistrer photo",this);


        mOpcionesMenu->addActions({ mEncenderAction,mApagarAction, mCapturarAction});
        ui->aaa->setMenu(mOpcionesMenu);




    mCamera->setViewfinder(mCameraViewfinder);

      m->addWidget(mCameraViewfinder);
      m->setMargin(0);
    ui->scrollArea->setLayout(m);
    connect(mEncenderAction,&QAction:: triggered,[&](){

    mCamera->start();
    });
    connect(mApagarAction,&QAction::triggered, [&](){
    mCamera->stop();
    });
      connect (mCapturarAction,&QAction::triggered, [&](){
          auto filename = QFileDialog:: getSaveFileName(this,"capturar","/",
                                                        "imagen (.jpg;.jpeg)");
          if(filename.isEmpty()){
              return;
          }
    mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageEncoderSettings;
    imageEncoderSettings.setCodec("image/jpeg");
    imageEncoderSettings.setResolution(1600,1200);
      mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
     mCamera->start();
     mCamera->searchAndLock();
     mCameraImageCapture->capture(filename);
     mCamera->unlock();

      });









    spectateurs tmp;
    ui->tableView->setModel(tmp.afficher());
     ui->tableView->setModel(tmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
            int age=ui->lineEdit_age->text().toInt();
            QString nom=ui->lineEdit_nom->text();
            QString prenom=ui->lineEdit_prenom->text();
            QString nationalite=ui->lineEdit_pays->text();
            QString type=ui->comboBox->currentText();


            spectateurs S(id,age,nom,prenom,nationalite,type);
            if(id==NULL){

                   QMessageBox::critical(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                    QObject::tr("Veuillez remplir tous les cases.\n"
                                                                "Click Cancel to exit ."),QMessageBox::Cancel);
                        }else if((nom=="") ||(S.verif_nom(nom)==false )){
                   QMessageBox::critical(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                    QObject::tr("le nom doit etre que des lettres.\n"
                                                                "Click Cancel to exit ."),QMessageBox::Cancel);

                        }else if((prenom=="") || (S.verif_nom(prenom)==false) ){
                   QMessageBox::critical(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                    QObject::tr("le prenom doit etre que des lettres.\n"
                                                                "Click Cancel to exit ."),QMessageBox::Cancel);

                       } else if((nationalite=="") || (S.verif_nom(nationalite)==false ))
            {
                   QMessageBox::critical(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                    QObject::tr("Veuillez saisir correctement la nationnalite.\n"
                                                                "Click Cancel to exit ."),QMessageBox::Cancel);
                           }
            else if((age==NULL )|| (S.verif_age(age)==false )){
                   QMessageBox::critical(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                    QObject::tr("Veuillez saisir correctement l'age.\n"
                                                                "Click Cancel to exit ."),QMessageBox::Cancel);
                        }



                        else{
               bool test=S.ajouter() ;
            if (test)
                {
                ui->tableView->setModel(S.afficher());
                QMessageBox::information(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                 QObject::tr("Client ajouté .\n"
                                                             "Click Cancel to exit ."),QMessageBox::Cancel);
                 }
            else
            {
                QMessageBox::critical(nullptr,QObject::tr("Ajouter un Spectateur"),
                                                 QObject::tr("Erreur.\n"
                                                             "Click Cancel to exit ."),QMessageBox::Cancel);
            }

               }

            }

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
      spectateurs s ;
       s.selectionner(ui,index);
     ui->lineEdit_id->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString());
}

void MainWindow::on_pushButton_supprimer_clicked()
{

        QSqlQuery qry;
        spectateurs c;


        bool test =c.supprimer(ui);
        if(test)
           {
            ui->tableView->setModel(c.afficher());

            QMessageBox::information(nullptr,QObject::tr("Supprimer un spectateur"),
                                             QObject::tr("spectateur sumprié .\n"
                                                         "Click Cancel to exit ."),QMessageBox::Cancel);

           }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("Supprimer un spectateur"),
                                             QObject::tr("Erreur.\n"
                                                         "Click Cancel to exit ."),QMessageBox::Cancel);
           }

}


void MainWindow::on_pushButton_4_clicked()
{
    spectateurs tmp;
    ui->tableView->setModel(tmp.afficher());
}


void MainWindow::on_pushButton_6_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    int age=ui->lineEdit_age->text().toInt();
       QString nom=ui->lineEdit_nom->text();
       QString prenom=ui->lineEdit_prenom->text();
       QString nationalite=ui->lineEdit_pays->text();
       QString type=ui->comboBox->currentText();

       spectateurs s;
              bool test;
              test=s.modifier(id,age,nom,prenom,nationalite,type);
              bool modifier(int id,int Age,QString nom,QString prenom,QString nationalite,QString type);
              if(test)
              {
                 ui->tableView->setModel(s.afficher());

                 QMessageBox::information(nullptr,QObject::tr("OK"),
                   QObject::tr(" spectateur modifé") ,QMessageBox::Ok);

               }else

                    QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                      QObject::tr("Erreur !.\n""Click Ok to exit."), QMessageBox::Ok);

}
void MainWindow::on_radioButton_clicked()
{
    spectateurs tmp;
    ui->tableView->setModel(tmp.trierASC());
}

void MainWindow::on_radioButton_2_clicked()
{
    spectateurs tmp;
    ui->tableView->setModel(tmp.trierDESC());
}
void MainWindow::on_pushButton_9_clicked(){
    spectateurs tmp;
          tmp.recherche(ui);

}

void MainWindow::on_pushButton_2_clicked(){
statistique s ;
s.exec();

}

void MainWindow::on_QR_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                        QObject::tr("Veuillez Choisir un identifiant.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {

                int le_id=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
                const QrCode qr = QrCode::encodeText(std::to_string(le_id).c_str(), QrCode::Ecc::LOW);
                std::ofstream myfile;
                myfile.open ("qrcode.svg") ;
                myfile << qr.toSvgString(1);
                myfile.close();
                QPixmap pix( QSize(90, 90) );
                QPainter pixPainter( &pix );
                QSvgRenderer svgRenderer(QString("qrcode.svg"));
                svgRenderer.render( &pixPainter );
                ui->QRCODE_3->setPixmap(pix);

           }
}



