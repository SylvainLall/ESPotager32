#include "core.h"
#include <Arduino.h>
#include <WebServer.h>



WebServer server(80);  // Initialisation de l'objet serveur Web

void initServeurWeb() {
    server.on("/", handleRoot);
    server.on("/submit", handleSubmit);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("Serveur web démarré en mode AP.");
}

void handleRoot() {
    String page = "<html><head><title>Controle Arrosage</title></head><body>";
    page += "<h1>ESPotager32</h1>";
    page += "<form action=\"/submit\" method=\"POST\">";

    // Ligne 1
    page += "<h2>Ligne 1</h2>";
    page += "Activer: <input type=\"radio\" name=\"etat1\" value=\"1\"";
    if (ligne1.etat == 1) page += " checked";
    page += "> Oui ";
    page += "<input type=\"radio\" name=\"etat1\" value=\"0\"";
    if (ligne1.etat == 0) page += " checked";
    page += "> Non<br>";
    page += "Heure: <input type=\"number\" name=\"h1\" value=\"" + String(ligne1.heure) + "\" min=\"0\" max=\"23\"> : ";
    page += "<input type=\"number\" name=\"m1\" value=\"" + String(ligne1.minute) + "\" min=\"0\" max=\"59\"><br>";
    page += "Duree (minutes): <input type=\"number\" name=\"d1\" value=\"" + String(ligne1.duree) + "\"><br>";
    page += "Frequence (jours): <input type=\"number\" name=\"f1\" value=\"" + String(ligne1.frequence) + "\" min=\"1\" max=\"30\"><br>";

    if (ligne1.etat == 1) {
        time_t now = time(nullptr);
        struct tm *currentTime = localtime(&now);
        int daysUntilNext = ligne1.frequence - (currentTime->tm_yday % ligne1.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne1.heure;
        nextWateringTime->tm_min = ligne1.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<span style='color:blue'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</span><br>";
    }

    // Ligne 2
    page += "<h2>Ligne 2</h2>";
    page += "Activer: <input type=\"radio\" name=\"etat2\" value=\"1\"";
    if (ligne2.etat == 1) page += " checked";
    page += "> Oui ";
    page += "<input type=\"radio\" name=\"etat2\" value=\"0\"";
    if (ligne2.etat == 0) page += " checked";
    page += "> Non<br>";
    page += "Heure: <input type=\"number\" name=\"h2\" value=\"" + String(ligne2.heure) + "\" min=\"0\" max=\"23\"> : ";
    page += "<input type=\"number\" name=\"m2\" value=\"" + String(ligne2.minute) + "\" min=\"0\" max=\"59\"><br>";
    page += "Duree (minutes): <input type=\"number\" name=\"d2\" value=\"" + String(ligne2.duree) + "\"><br>";
    page += "Frequence (jours): <input type=\"number\" name=\"f2\" value=\"" + String(ligne2.frequence) + "\" min=\"1\" max=\"30\"><br>";

    if (ligne2.etat == 1) {
        time_t now = time(nullptr);
        struct tm *currentTime = localtime(&now);
        int daysUntilNext = ligne2.frequence - (currentTime->tm_yday % ligne2.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne2.heure;
        nextWateringTime->tm_min = ligne2.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<span style='color:blue'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</span><br>";
    }

    // Ligne 3
    page += "<h2>Ligne 3</h2>";
    page += "Activer: <input type=\"radio\" name=\"etat3\" value=\"1\"";
    if (ligne3.etat == 1) page += " checked";
    page += "> Oui ";
    page += "<input type=\"radio\" name=\"etat3\" value=\"0\"";
    if (ligne3.etat == 0) page += " checked";
    page += "> Non<br>";
    page += "Heure: <input type=\"number\" name=\"h3\" value=\"" + String(ligne3.heure) + "\" min=\"0\" max=\"23\"> : ";
    page += "<input type=\"number\" name=\"m3\" value=\"" + String(ligne3.minute) + "\" min=\"0\" max=\"59\"><br>";
    page += "Duree (minutes): <input type=\"number\" name=\"d3\" value=\"" + String(ligne3.duree) + "\"><br>";
    page += "Frequence (jours): <input type=\"number\" name=\"f3\" value=\"" + String(ligne3.frequence) + "\" min=\"1\" max=\"30\"><br>";

    if (ligne3.etat == 1) {
        time_t now = time(nullptr);
        struct tm *currentTime = localtime(&now);
        int daysUntilNext = ligne3.frequence - (currentTime->tm_yday % ligne3.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne3.heure;
        nextWateringTime->tm_min = ligne3.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<span style='color:blue'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</span><br>";
    }

    // Ligne 4
    page += "<h2>Ligne 4</h2>";
    page += "Activer: <input type=\"radio\" name=\"etat4\" value=\"1\"";
    if (ligne4.etat == 1) page += " checked";
    page += "> Oui ";
    page += "<input type=\"radio\" name=\"etat4\" value=\"0\"";
    if (ligne4.etat == 0) page += " checked";
    page += "> Non<br>";
    page += "Heure: <input type=\"number\" name=\"h4\" value=\"" + String(ligne4.heure) + "\" min=\"0\" max=\"23\"> : ";
    page += "<input type=\"number\" name=\"m4\" value=\"" + String(ligne4.minute) + "\" min=\"0\" max=\"59\"><br>";
    page += "Duree (minutes): <input type=\"number\" name=\"d4\" value=\"" + String(ligne4.duree) + "\"><br>";
    page += "Frequence (jours): <input type=\"number\" name=\"f4\" value=\"" + String(ligne4.frequence) + "\" min=\"1\" max=\"30\"><br>";

    if (ligne4.etat == 1) {
        time_t now = time(nullptr);
        struct tm *currentTime = localtime(&now);
        int daysUntilNext = ligne4.frequence - (currentTime->tm_yday % ligne4.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne4.heure;
        nextWateringTime->tm_min = ligne4.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<span style='color:blue'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</span><br>";
    }

    page += "<input type=\"submit\" value=\"Mettre a jour\">";
    page += "</form></body></html>";

    server.send(200, "text/html", page);
}



void handleSubmit() {
    if (server.hasArg("etat1")) ligne1.etat = server.arg("etat1").toInt();
    if (server.hasArg("h1")) ligne1.heure = server.arg("h1").toInt();
    if (server.hasArg("m1")) ligne1.minute = server.arg("m1").toInt();
    if (server.hasArg("d1")) ligne1.duree = server.arg("d1").toInt();
    if (server.hasArg("f1")) ligne1.frequence = server.arg("f1").toInt();

    if (server.hasArg("etat2")) ligne2.etat = server.arg("etat2").toInt();
    if (server.hasArg("h2")) ligne2.heure = server.arg("h2").toInt();
    if (server.hasArg("m2")) ligne2.minute = server.arg("m2").toInt();
    if (server.hasArg("d2")) ligne2.duree = server.arg("d2").toInt();
    if (server.hasArg("f2")) ligne2.frequence = server.arg("f2").toInt();

    if (server.hasArg("etat3")) ligne3.etat = server.arg("etat3").toInt();
    if (server.hasArg("h3")) ligne3.heure = server.arg("h3").toInt();
    if (server.hasArg("m3")) ligne3.minute = server.arg("m3").toInt();
    if (server.hasArg("d3")) ligne3.duree = server.arg("d3").toInt();
    if (server.hasArg("f3")) ligne3.frequence = server.arg("f3").toInt();

    if (server.hasArg("etat4")) ligne4.etat = server.arg("etat4").toInt();
    if (server.hasArg("h4")) ligne4.heure = server.arg("h4").toInt();
    if (server.hasArg("m4")) ligne4.minute = server.arg("m4").toInt();
    if (server.hasArg("d4")) ligne4.duree = server.arg("d4").toInt();
    if (server.hasArg("f4")) ligne4.frequence = server.arg("f4").toInt();

 // Sauvegarder TOUS les paramètres dans NVS
//----------TODO : ne sauvegarder que les parametres modifier pour eviter d'ecraser toute la memoire a chaque modif
    sauvegarderParametres();

     // Répondre à la demande
    server.send(200, "text/html", "<html><body><h1>Parametres mis a jour !</h1><a href=\"/\">Retour</a></body></html>");
}

void handleNotFound() {
    server.send(404, "text/plain", "Page non trouvee !");
}
