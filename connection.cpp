    #include "connection.h"
#include <QDebug>

Connection::Connection(){}

bool Connection::createconnection()
{
    bool test=false;
QSqlDatabase abbassi_db = QSqlDatabase::addDatabase("QODBC");
abbassi_db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
abbassi_db.setUserName("mouhamed");//inserer nom de l'utilisateur
abbassi_db.setPassword("abbassi");//inserer mot de passe de cet utilisateur

if (abbassi_db.open())
test=true;

    return  test;
}
void Connection::closeconnection(){abbassi_db.close();}
