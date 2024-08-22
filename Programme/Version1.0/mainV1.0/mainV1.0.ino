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
                                                         "Y88P"         V1.0                        

*/




#include "core.h"
#include <WiFi.h>
#include <WebServer.h>

void setup() {
    Serial.begin(115200);
// Initialiser le stockage memoire NVS
    initNVS();
// Charger les paramètres depuis NVS
    chargerParametres();
    bool heureAJour = 0;

    // Configuration du mode AP
    WiFi.softAP("ESPotager32", "1234");  // Changez le SSID et le mot de passe si nécessaire
    Serial.println("Point d'accès démarré");
    Serial.println("IP de l'AP: " + WiFi.softAPIP().toString());

    initRelais();      // Initialiser les relais
    initServeurWeb();  // Initialiser le serveur web
}

void loop() {
    server.handleClient();  // Gérer les requêtes clients
    gererArrosage();        // Gérer l'arrosage
}
