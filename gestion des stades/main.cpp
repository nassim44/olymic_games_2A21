#include "gestion_des_jeux.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"olympic_games.h"
#include "admin.h"
#include "ui_admin.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include"gestion_des_stades.h"
#include"location.h"
#include"QQmlApplicationEngine"


//#include"gestion_des_jeux.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


   Connection c;
   admin A;
gestion_des_stades G;
//nassim map______________________
   qmlRegisterType<Location>("Location",1,0,"Stade");
   Stade s;
   Location cppLocation;
   Location cppLocationCopy;

   cppLocation.setLocation(36.839448552924246);
   QQmlApplicationEngine engine;
//   engine.rootContext()->setContextProperty("cppLocation", &cppLocation);
//   engine.rootContext()->setContextProperty("cppLocationCopy", &cppLocationCopy);
//   engine.load(QUrl(QStringLiteral("qrc:/Map.qml")));





    bool test=c.createconnection();//Etablir la connexion

//    Gestion_des_jeux w;
//    w.setWindowState(Qt::WindowFullScreen);//Fullscreen
//    w.show();
    if(test)
    {
        //w.show();
        A.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();

   }
