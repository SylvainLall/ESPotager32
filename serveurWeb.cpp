#include "core.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>


// Définir le SSID et le mot de passe du point d'accès
const char* ssidAP = "arrosageAuto2";
const char* passwordAP = "cinamone";


// initialisation des variables privées : 
int ecoMode = 0;
int normalMode = 0;
int degradeMode = 1;

// Initialiser le serveur web sur le port 80
WebServer server(80);

void setupServeurWeb() {
WiFi.softAP(ssidAP, passwordAP);
// WiFi.config(ip, gateway, subnet);  a decommenter et remplir si besoin reseau spécifique
server.on("/", handleRoot);
server.on("/mode", handleMode);
server.on("/vidange", handleVidange);
server.on("/setDateTime", handleSetDateTime);
timeClient.begin();
server.begin();
}

void handleRoot() {
  String heure = "<script>document.write(new Date().toLocaleTimeString());</script>";

  String html = "<html><body><h2><p>" + heure + "</h2></p>";
  // Obtenir l'heure actuelle
 
  html += "<h3>Envoyer l'heure et la date a l'ESP32</h3>";
  html += "<button onclick=\"sendDateTime()\">Envoyer</button>";
  html += "<span id=\"confirmation\"></span>"; // Élément pour afficher le message de confirmation
  html += "<script>";
  html += "function sendDateTime() {";
  html += "  var currentTime = new Date();";
  html += "  var year = currentTime.getFullYear();";
  html += "  var month = currentTime.getMonth() + 1;";
  html += "  var day = currentTime.getDate();";
  html += "  var hours = currentTime.getHours();";
  html += "  var minutes = currentTime.getMinutes();";
  html += "  var seconds = currentTime.getSeconds();";
  html += "  var datetime = year + '-' + month + '-' + day + ' ' + hours + ':' + minutes + ':' + seconds;";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/setDateTime?datetime=' + datetime, true);";
  html += "  xhr.send();";
   html += "  document.getElementById('confirmation').innerHTML = 'Date et heure mises a jour';"; // Afficher le message de confirmation
  html += "}";
  html += "</script>";
  html += "<style>h2 {font-size: 3em;}</style>";
  html += " <h1>ESP8266 -arrosage automatique</h1>";

  html += "<form action='/mode'>";
  html += "<br>";
  html += "<input type='radio' name='mode' value='eco' ";

  if (ecoMode == 1) {
    html += "checked";
  }
  html += ">Eco<br>";
  html += "<br>";
  html += "<input type='radio' name='mode' value='normal' ";
  if (normalMode == 1) {
    html += "checked";
  }
  html += ">Normal<br>";
  html += "<br>";
  html += "<input type='radio' name='mode' value='degrade' ";
  if (degradeMode == 1) {
    html += "checked";
  }
  html += ">Degrade <i>(si capteur de niveau cuve HS)</i><br>";
  html += "<br>";
  html += "<input type='submit' value='Choisir'>";
  html += "</form>";

  html += "<h1>Menu de vidange</h1>";
  html += "<form action='/vidange' method='get'>";
  html += "<select name='tempsVidange'>";
  html += "<option value='0'>0</option>";
  html += "<option value='15s'>15 secondes</option>";
  html += "<option value='15min'>15 minutes</option>";
  html += "<option value='1h'>1 heure</option>";
  html += "<option value='4h'>4 heures</option>";
  html += "</select>";
  html += "<br><br><input type='submit' value='lancer'>";
  html += "</form>";
  html += "<p> heure de la derniere vidange :"  + String(derniereVidange) + "</p>" ;
          html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSetDateTime() {
  if (server.hasArg("datetime")) {
    String datetime = server.arg("datetime");

    // Extraire les informations de date et d'heure
    int year, month, day, hours, minutes, seconds;
    sscanf(datetime.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);

    // Mettre à jour l'horloge interne de l'ESP32
    setTime(hours, minutes, seconds, day, month, year);

    server.send(204); // Réponse vide avec code d'état HTTP 204 (No Content)
  } else {
    server.send(400, "text/plain", "Paramètre 'datetime' manquant");
  }
}
void handleMode() {
  if (server.hasArg("mode")) {
    String mode1 = server.arg("mode");
    Serial.print("Mode choisi : ");
    Serial.println(mode1);
    // mettre à jour la variable correspondante
    if (mode1 == "eco") {
      ecoMode = 1;
      normalMode = 0;
      degradeMode = 0;

    } else if (mode1 == "normal") {
      ecoMode = 0;
      normalMode = 1;
      degradeMode = 0;
    } else if (mode1 == "degrade") {
      ecoMode = 0;
      normalMode = 0;
      degradeMode = 1;
    }
    server.sendHeader("Location", "/");
    server.send(200, "text/plain", "valeur modifiee");

  }
}
void handleVidange() {
  if (server.hasArg("tempsVidange")) {
    String tempsVidangeValue = server.arg("tempsVidange");
    Serial.print("Temps de vidange choisi : ");
    Serial.println(tempsVidangeValue);

    if (tempsVidangeValue == "0") {
      tempsVidange = 0;
    } else if (tempsVidangeValue == "15s") {
      tempsVidange = 15000;
    } else if (tempsVidangeValue == "15min") {
      tempsVidange = 1800000;
    } else if (tempsVidangeValue == "1h") {
      tempsVidange = 3600000;
    } else if (tempsVidangeValue == "4h") {
      tempsVidange = 14400000;
    }
  }
  server.send(200, "text/html", "Temps vidange choisi ");
}