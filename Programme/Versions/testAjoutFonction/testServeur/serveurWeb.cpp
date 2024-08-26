#include "core.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Initialisation des variables
const char* ssid = "arrosageauto";
const char* password = "1234";

int currentValue ;  // Valeur par défaut


WebServer server(80);  // Création du serveur web sur le port 80

void initWiFi() {
  
  WiFi.softAP(ssid, password);
  Serial.print("Point d'accès créé. Adresse IP : ");
  Serial.println(WiFi.softAPIP());
}

void handleRoot() {
  // Génération dynamique du menu déroulant avec la valeur actuelle sélectionnée
  String html = "<html>\
                 <head>\
                   <title>ESPotager32</title>\
                   <style>\
                     body { font-size: 24px; } /* Augmente la taille de la police par défaut */\
                     h1 { font-size: 64px; }   /* Taille de la police pour le titre */\
                     select { font-size: 32px; padding: 5px; } /* Taille de la police du menu déroulant */\
                     input[type='submit'] { font-size: 32px; padding: 10px; } /* Taille et padding du bouton */\
                   </style>\
                 </head>\
                 <body>\
                   <h1>ESPotager32</h1>\
                   <form action='/setVariable' method='GET'>\
                     <label for='variable'>Choisir une valeur :</label>\
                     <select name='variable' id='variable'>";

  for (int i = 1; i <= 4; i++) {
    if (i == currentValue) {
      html += "<option value='" + String(i) + "' selected>" + String(i) + "</option>";
    } else {
      html += "<option value='" + String(i) + "'>" + String(i) + "</option>";
    }
  }

  html += "</select>\
           <input type='submit' value='Valider'>\
           </form>\
           </body>\
           </html>";

  server.send(200, "text/html", html);
}


void handleSetVariable() {
  // Met à jour la valeur de currentValue avec celle sélectionnée par l'utilisateur
  if (server.hasArg("variable")) {
    currentValue = server.arg("variable").toInt();  // Convertir la valeur reçue en entier
  }

  // Réponse pour l'utilisateur après avoir soumis le formulaire
  String response = "<html><body><h1>Valeur choisie : " + String(currentValue) + "</h1><br><a href='/'>Retour</a></body></html>";
  server.send(200, "text/html", response);
}

void initServer() {
  server.on("/", handleRoot);
  server.on("/setVariable", handleSetVariable);
  server.begin();
  Serial.println("Serveur démarré.");
}

void handleClient() {
  server.handleClient();
}