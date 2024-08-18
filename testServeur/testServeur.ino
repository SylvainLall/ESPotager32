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
                                                         "Y88P"          by KELIOVeille-techno                             

*/




#include "core.h"

void setup() {
  const char* ssid = "ESPotager32";
const char* password = "1234";
  Serial.begin(115200);  // Initialisation de la communication série à 115200 bauds
initWiFi();     // Initialisation du Wi-Fi
initServer();   // Initialisation du serveur web
}

void loop() {
 handleClient(); // Gestion des requêtes des clients

  
}