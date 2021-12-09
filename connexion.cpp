
#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::ouvrirConnexion()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("baha-bd");//inserer le nom de la source de données ODBC
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("cab");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





   return  test;
}
void Connexion::fermerConnexion(){db.close();}
