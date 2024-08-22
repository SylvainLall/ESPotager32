#ifndef CORE_H
#define CORE_H

#include <WebServer.h> 
extern const char* ssid;
extern const char* password;





//---------------------------------------core.cpp---------------------------------
// Structure pour stocker les paramètres d'arrosage
struct LigneArrosage {
    int heure;
    int minute;
    int duree;  // Durée en minutes
    int relaisPin;  // Pin du relais
    int etat;  // 0: Désactivé, 1: Activé
    int frequence;     // Fréquence d'arrosage en jours
};

// Déclaration des lignes d'arrosage
extern LigneArrosage ligne1;
extern LigneArrosage ligne2;
extern LigneArrosage ligne3;
extern LigneArrosage ligne4;

void initRelais();
void gererArrosage();

//---------------------------------------serveurWeb.cpp---------------------------
extern WebServer server;

void initServeurWeb();
void handleRoot();
void handleNotFound();
void handleSubmit();

//---------------------------------------memorisation.cpp--------------------------
void initNVS();
void sauvegarderParametres();
void chargerParametres();


#endif // CORE_H