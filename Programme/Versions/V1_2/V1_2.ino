/*

8888888888 .d8888b.  8888888b.          888                                      .d8888b.   .d8888b.  
888       d88P  Y88b 888   Y88b         888                                     d88P  Y88b d88P  Y88b 
888       Y88b.      888    888         888                                          .d88P        888 
8888888    "Y888b.   888   d88P .d88b.  888888  8888b.   .d88b.   .d88b.  888d888   8888"       .d88P 
888           "Y88b. 8888888P" d88""88b 888        "88b d88P"88b d8P  Y8b 888P"      "Y8b.  .od888P"  
888             "888 888       888  888 888    .d888888 888  888 88888888 888   888    888 d88P"      
888       Y88b  d88P 888       Y88..88P Y88b.  888  888 Y88b 888 Y8b.     888   Y88b  d88P 888"       
8888888888 "Y8888P"  888        "Y88P"   "Y888 "Y888888  "Y88888  "Y8888  888    "Y8888P"  888888888  
                                                             888                                      
                                                        Y8b d88P                                      
                                                         "Y88P"         V1.1                        

*/



#include "core.h"
#include <WiFi.h>
#include <WebServer.h>

#define WIFI_BUTTON_PIN 5  // PIN du bouton pour activer le Wi-Fi
#define WIFI_TIMEOUT_MS 900000 // 15m en millisecondes

unsigned long wifiStartMillis = 0;
bool wifiActive = false;

void activerWifi() {
    WiFi.softAP("ESPotager32", "1234");  // Changez le SSID et le mot de passe si nécessaire
    Serial.println("Wi-Fi active en mode Point d'acces");
    Serial.println("IP de l'AP: " + WiFi.softAPIP().toString());
    wifiActive = true;
    wifiStartMillis = millis();  // Enregistre l'heure d'activation
}

void desactiverWifi() {
    WiFi.softAPdisconnect(true);  // Déconnecte le mode Point d'accès
    Serial.println("Wi-Fi désactive");
    wifiActive = false;
}

void setup() {
    Serial.begin(115200);

    // Initialiser le stockage mémoire NVS
    initNVS();
    chargerParametres();

    pinMode(WIFI_BUTTON_PIN, INPUT_PULLUP);  // Configuration du bouton avec pull-up

    initRelais();      // Initialiser les relais
    initServeurWeb();  // Initialiser le serveur web

    initLogSystem(server);    
    ajouterLog("Demarrage du systeme");
}

void loop() {
    server.handleClient();  // Gérer les requêtes clients
    gererArrosage();        // Gérer l'arrosage

    // Vérifie si le bouton est pressé et active le Wi-Fi si nécessaire
    if (digitalRead(WIFI_BUTTON_PIN) == LOW) {  // Si bouton pressé
        delay(50);  // Anti-rebond
        if (digitalRead(WIFI_BUTTON_PIN) == LOW && !wifiActive) {  // Si toujours pressé et Wi-Fi inactif
            activerWifi();
            ajouterLog("Activation du Wi-Fi pour 15min");
        }
    }

    // Désactive le Wi-Fi après une heure
    if (wifiActive && (millis() - wifiStartMillis >= WIFI_TIMEOUT_MS)) {
        desactiverWifi();
        ajouterLog("Désactivation automatique du Wi-Fi");
    }
}