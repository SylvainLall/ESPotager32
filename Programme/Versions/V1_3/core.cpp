/*
    Description :
    -------------
    Ce programme gère un système d'arrosage automatique en utilisant l'ESP32. 
    Chaque ligne d'arrosage peut être programmée avec une heure de début, 
    une durée et une fréquence (en jours) d'arrosage.

    Fonctionnalités principales :
    -----------------------------
    - Activation des lignes d'arrosage à une heure précise et pour une durée définie.
    - Gestion de la fréquence d'arrosage pour chaque ligne (exprimée en jours).
    - Enregistrement de chaque activation et désactivation dans un log.

    Fonctions principales :
    -----------------------
    - `initRelais()`     : Configure les pins des relais et synchronise l'heure via NTP.
    - `gererArrosage()`  : Gère les cycles d'activation/désactivation des relais selon les horaires et la durée définis.
    - `ajouterLog()`     : Enregistre un message pour chaque activation et désactivation de ligne dans le système de log.

    ============================================================
*/


#include "core.h"
#include <time.h>  // Bibliothèque pour gérer le temps sur l'ESP32
#include <Arduino.h>

// LES PIN DES RELAIS SONT A REMPLIR ICI !!!
LigneArrosage ligne1 = {6, 0, 30, 22, 0, 1};  // Par défaut : 6h, 0 min ,duree 30 min, PIN 15, etat desactivé, frequence arrosage 1
LigneArrosage ligne2 = {6, 0, 30, 14, 0, 1};
LigneArrosage ligne3 = {6, 0, 30, 33, 0, 1};
LigneArrosage ligne4 = {6, 0, 30, 34, 0, 1};

void initRelais() {
    pinMode(ligne1.relaisPin, OUTPUT);
    pinMode(ligne2.relaisPin, OUTPUT);
    pinMode(ligne3.relaisPin, OUTPUT);
    pinMode(ligne4.relaisPin, OUTPUT);

    digitalWrite(ligne1.relaisPin, HIGH);
    digitalWrite(ligne2.relaisPin, HIGH);
    digitalWrite(ligne3.relaisPin, HIGH);
    digitalWrite(ligne4.relaisPin, HIGH);

    configTime(0, 0, "pool.ntp.org");  // Synchronisation NTP si relié au reseau wifi
}
unsigned long lastMillis[4] = {0, 0, 0, 0};  // Temps de début de l'arrosage pour chaque ligne
bool arrosageEnCours[4] = {false, false, false, false};  // Indique si l'arrosage est en cours pour chaque ligne
int dernierJourArrosage[4] = {-1, -1, -1, -1};  // Jour de l'année du dernier arrosage pour chaque ligne

void gererArrosage() {
    time_t now = time(nullptr);
    struct tm *currentTime = localtime(&now);
    int jourActuel = currentTime->tm_yday;

    LigneArrosage lignes[4] = {ligne1, ligne2, ligne3, ligne4};

    for (int i = 0; i < 4; i++) {
        LigneArrosage &ligne = lignes[i];

        if (ligne.etat == 1) { // Vérifie si la ligne est activée
            // Vérifie si la fréquence d'arrosage est respectée
            if (dernierJourArrosage[i] == -1 || (jourActuel - dernierJourArrosage[i]) >= ligne.frequence) {
                
                // Si l'arrosage n'a pas encore commencé et que l'heure est atteinte
                if (!arrosageEnCours[i] && currentTime->tm_hour == ligne.heure && currentTime->tm_min == ligne.minute) {
                    digitalWrite(ligne.relaisPin, LOW); // Activer le relais
                    lastMillis[i] = millis(); // Enregistrer le temps de début
                    arrosageEnCours[i] = true; // Marquer l'arrosage comme en cours
                    Serial.print("activation de la ligne ");
                    Serial.println((i+1));
                    ajouterLog("activation de la ligne " + String(i + 1));
                    dernierJourArrosage[i] = jourActuel; // Mettre à jour le jour du dernier arrosage
                }
              }
                // Si l'arrosage est en cours et que la durée est écoulée
                if (arrosageEnCours[i] && millis() - lastMillis[i] >= ligne.duree * 60000) {
                    digitalWrite(ligne.relaisPin, HIGH); // Désactiver le relais
                    Serial.print("desactivation de la ligne");
                    Serial.println((i+1));
                    ajouterLog("desactivation de la ligne " + String(i + 1));
                    arrosageEnCours[i] = false; // Marquer l'arrosage comme terminé
                }
            
        }
    }
}
