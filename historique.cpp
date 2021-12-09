#include "historique.h"
#include<QMessageBox>

Historique::Historique()
{
tmp="";
}
void Historique::save(QString idj,QString nom,QString pays)
{    QFile file ("C:/Users/Admin/Desktop/gestion_joueurs/his.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << idj+"\n"+nom << "\n" +pays << "\n";


}
QString Historique::load()
{   tmp="";

    QFile file(" C:/Users/Admin/Desktop/gestion_joueurs/his.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
