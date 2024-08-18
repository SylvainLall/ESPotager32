#ifndef CORE_H
#define CORE_H

extern int niveauPourcent;  // pourcentage restant d'eau dans la cuve

void mesureNiveau();          //mesure.cpp
void  setupMesure();          //mesure.cpp

void afficherNiveau();        //affichage.cpp

void setupServeurWeb();       //serveurWeb.cpp 
void handleMode();            //serveurWeb.cpp 
void handleSetDateTime();     //serveurWeb.cpp
void handleRoot();            //serveurWeb.cpp
void handleVidange();         //serveurWeb.cpp
void server.handleClient();
#endif // CORE_H