#include "connexion.h"


//mod
connexion::connexion()

{

}

bool connexion::create_cnx(){



    bool test=false;

    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("test-db");

    db.setUserName("sahar");

    db.setPassword("sahar");

    if(db.open())

        test=true;

    return test;

}



void connexion::close_cnx(){db.close();}
