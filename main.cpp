#include "gestion_des_jeux.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"jeux.h"
#include"gestion_des_jeux.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gestion_des_jeux w;
    Connection c;
    bool test=c.createconnection();//Etablir la connexion

    if(test)
    {w.show();
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
