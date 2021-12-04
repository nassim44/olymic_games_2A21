#include "gestion_des_jeux.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"olympic_games.h"
#include "admin.h"
#include "ui_admin.h"

//#include"gestion_des_jeux.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


   admin A;
   Connection c;

    bool test=c.createconnection();//Etablir la connexion
//bool test1=A.connOpen();




    Gestion_des_jeux w;
   // w.setWindowState(Qt::WindowFullScreen);//Fullscreen
    //w.show();






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
