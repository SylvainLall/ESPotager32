/*
    Description :
    -------------
    Ce fichier regroupe les déclarations de structures, variables,
    et fonctions utilisées dans le système d'arrosage automatique.
    Il permet l'organisation et l'accès aux différentes fonctions
    de gestion des relais, serveur web, mémorisation des paramètres,
    et enregistrement des logs.

    Variables principales :
    -----------------------
    - `const char* ssid` et `const char* password` : Identifiants de connexion Wi-Fi.
    - `LigneArrosage ligne1, ligne2, ligne3, ligne4` : Configuration des 4 lignes d'arrosage.

    Structures :
    ------------
    - `struct LigneArrosage` : Stocke les paramètres d'une ligne d'arrosage, incluant heure, minute, durée, pin relais, état et fréquence.

    Fonctions principales :
    -----------------------
    - `initRelais()`             : Initialise les pins des relais.
    - `gererArrosage()`          : Gère les cycles d'arrosage selon les paramètres.
    - `initServeurWeb()`         : Initialise le serveur web pour la configuration.
    - `handleRoot()`, `handleNotFound()`, etc. : Gestion des différentes pages du serveur web.
    - `initNVS()`, `sauvegarderParametres()`, `chargerParametres()` : Gestion du stockage et de la récupération des paramètres dans le NVS.
    - `initLogSystem()`, `ajouterLog()` : Système d'enregistrement et d'affichage des logs pour suivre l'activité du système.

    Remarque :
    ----------
    Ce fichier doit être inclus dans les fichiers d'implémentation
    pour accéder aux fonctionnalités principales du système.
    Je n'ai fait qu'un seul fichier .h pour eviter d'en avoir un par cpp. 
    mais il faut bien séparé les variables par page en les séparant par des "-------truc.cpp-------"  
    
*/


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
extern bool heureAJour;
void initServeurWeb();
void handleRoot();
void handleNotFound();
void handleSubmit();
void handleSetTime();

//---------------------------------------memorisation.cpp--------------------------
void initNVS();
void sauvegarderParametres();
void chargerParametres();

// -------------------------------------- logger.cpp ----------------------------------

void handleLog();
void ajouterLog(const String &message);

//----------------------------------------configuration.cpp ---------------------------
void handleConfig();

#endif // CORE_H


