#include "core.h"
#include <Preferences.h>
// Instance de Preferences
Preferences preferences;


void initNVS() {
    // Initialiser NVS avec le namespace "arrosage"
    preferences.begin("arrosage", false);
}

void sauvegarderParametres() {
    preferences.putInt("ligne1_etat", ligne1.etat);
    preferences.putInt("ligne1_heure", ligne1.heure);
    preferences.putInt("ligne1_minute", ligne1.minute);
    preferences.putInt("ligne1_duree", ligne1.duree);
    preferences.putInt("ligne1_frequence", ligne1.frequence);

    preferences.putInt("ligne2_etat", ligne2.etat);
    preferences.putInt("ligne2_heure", ligne2.heure);
    preferences.putInt("ligne2_minute", ligne2.minute);
    preferences.putInt("ligne2_duree", ligne2.duree);
    preferences.putInt("ligne2_frequence", ligne2.frequence);

    preferences.putInt("ligne3_etat", ligne3.etat);
    preferences.putInt("ligne3_heure", ligne3.heure);
    preferences.putInt("ligne3_minute", ligne3.minute);
    preferences.putInt("ligne3_duree", ligne3.duree);
    preferences.putInt("ligne3_frequence", ligne3.frequence);

    preferences.putInt("ligne4_etat", ligne4.etat);
    preferences.putInt("ligne4_heure", ligne4.heure);
    preferences.putInt("ligne4_minute", ligne4.minute);
    preferences.putInt("ligne4_duree", ligne4.duree);
    preferences.putInt("ligne4_frequence", ligne4.frequence);

    Serial.println("Parametres sauvegardes dans NVS");
}

void chargerParametres() {
    ligne1.etat = preferences.getInt("ligne1_etat", 0);
    ligne1.heure = preferences.getInt("ligne1_heure", 0);
    ligne1.minute = preferences.getInt("ligne1_minute", 0);
    ligne1.duree = preferences.getInt("ligne1_duree", 0);
    ligne1.frequence = preferences.getInt("ligne1_frequence", 1);


    ligne2.etat = preferences.getInt("ligne2_etat", 0);
    ligne2.heure = preferences.getInt("ligne2_heure", 0);
    ligne2.minute = preferences.getInt("ligne2_minute", 0);
    ligne2.duree = preferences.getInt("ligne2_duree", 0);
    ligne2.frequence = preferences.getInt("ligne2_frequence", 1);

    ligne3.etat = preferences.getInt("ligne3_etat", 0);
    ligne3.heure = preferences.getInt("ligne3_heure", 0);
    ligne3.minute = preferences.getInt("ligne3_minute", 0);
    ligne3.duree = preferences.getInt("ligne3_duree", 0);
    ligne3.frequence = preferences.getInt("ligne3_frequence", 1);

    ligne4.etat = preferences.getInt("ligne4_etat", 0);
    ligne4.heure = preferences.getInt("ligne4_heure", 0);
    ligne4.minute = preferences.getInt("ligne4_minute", 0);
    ligne4.duree = preferences.getInt("ligne4_duree", 0);
    ligne4.frequence = preferences.getInt("ligne4_frequence", 1);

    Serial.println("Parametres charges depuis NVS");
}

void closeNVS() {
    preferences.end(); // Ferme le stockage NVS
}
