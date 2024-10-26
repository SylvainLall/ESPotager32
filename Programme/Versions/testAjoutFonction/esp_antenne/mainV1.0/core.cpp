#include "core.h"
#include <time.h>  // Bibliothèque pour gérer le temps sur l'ESP32
#include <Arduino.h>

// LES PIN DES RELAIS SONT A REMPLIR ICI !!!
LigneArrosage ligne1 = {6, 0, 30, 22, 0, 1};  // Par défaut : 6h, 0 min ,duree 30 min, PIN 15, etat desactivé, frequence arrosage 1
LigneArrosage ligne2 = {6, 0, 30, 23, 0, 1};
LigneArrosage ligne3 = {6, 0, 30, 18, 0, 1};
LigneArrosage ligne4 = {6, 0, 30, 19, 0, 1};

void initRelais() {
    pinMode(ligne1.relaisPin, OUTPUT);
    pinMode(ligne2.relaisPin, OUTPUT);
    pinMode(ligne3.relaisPin, OUTPUT);
    pinMode(ligne4.relaisPin, OUTPUT);

    digitalWrite(ligne1.relaisPin, LOW);
    digitalWrite(ligne2.relaisPin, LOW);
    digitalWrite(ligne3.relaisPin, LOW);
    digitalWrite(ligne4.relaisPin, LOW);

    configTime(0, 0, "pool.ntp.org");  // Synchronisation NTP
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
                    digitalWrite(ligne.relaisPin, HIGH); // Activer le relais
                    lastMillis[i] = millis(); // Enregistrer le temps de début
                    arrosageEnCours[i] = true; // Marquer l'arrosage comme en cours
                    dernierJourArrosage[i] = jourActuel; // Mettre à jour le jour du dernier arrosage
                }
              }
                // Si l'arrosage est en cours et que la durée est écoulée
                if (arrosageEnCours[i] && millis() - lastMillis[i] >= ligne.duree * 60000) {
                    digitalWrite(ligne.relaisPin, LOW); // Désactiver le relais
                    arrosageEnCours[i] = false; // Marquer l'arrosage comme terminé
                }
            
        }
    }
}
