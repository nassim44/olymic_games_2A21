#include "connection.h"
#include <QDebug>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("eyayassmine");//inserer nom de l'utilisateur
db.setPassword("eyayassmine");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

else
    qDebug()<< db.lastError().text();


    return  test;
}
