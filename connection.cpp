#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{bool test=false;
 db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données ODBC
db.setUserName("Soumaya");//inserer nom de l'utilisateur
db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

if (db.open())test=true;
test=true;


    return  test;
}
