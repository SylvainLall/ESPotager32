#include "core.h"
#include <Arduino.h>
#include <WebServer.h>
#include <time.h> 

bool heureAJour; // flag qui repasse a 0 a chaque demarrage de l'esp
WebServer server(80);  // Initialisation de l'objet serveur Web

void initServeurWeb() {
    server.on("/", handleRoot);
    server.on("/submit", handleSubmit);
    server.onNotFound(handleNotFound);
    server.on("/setTime", handleSetTime);
    

    server.begin();
    Serial.println("Serveur web démarré en mode AP.");
}
void handleRoot() {
    String page = "<!DOCTYPE html><html><head><title>Controle Arrosage</title>";
    page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; margin: 0; padding: 20px; background-color: #f4f4f4; }";
    page += "h1, h2 { color: #333; }";
    page += "h3 { color: #555; }";
    page += "form { background: #fff; padding: 15px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); margin-bottom: 20px; }";
    page += "input[type='number'], input[type='radio'] { margin-bottom: 10px; }";
    page += "input[type='submit'], button { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; }";
    page += "input[type='submit']:hover, button:hover { background-color: #45a049; }";
    page += ".alert { color: red; font-weight: bold; }";
    page += ".info { color: blue; }";
    page += "</style>";
    page += "<script type='text/javascript'>";
    page += "function mettreAHeure() {";
    page += "  var now = new Date();";
    page += "  var heure = now.getHours();";
    page += "  var minutes = now.getMinutes();";
    page += "  var secondes = now.getSeconds();";
    page += "  var jour = now.getDate();";
    page += "  var mois = now.getMonth() + 1;";
    page += "  var annee = now.getFullYear();";
    page += "  var xhr = new XMLHttpRequest();";
    page += "  xhr.open('GET', '/setTime?heure=' + heure + '&minutes=' + minutes + '&secondes=' + secondes + '&jour=' + jour + '&mois=' + mois + '&annee=' + annee, true);";
    page += "  xhr.send();";
    page += "}";
    page += "</script></head><body>";

    // Affichage de l'heure actuelle
    time_t now = time(nullptr);
    struct tm *currentTime = localtime(&now);

    page += "<h1>ESPotager32</h1>";
    page += "<h3 id='dateActuelle'>Heure actuelle: " + String(currentTime->tm_hour) + ":" + (currentTime->tm_min < 10 ? "0" : "") + String(currentTime->tm_min) +
            " le " + String(currentTime->tm_mday) + "/" + String(currentTime->tm_mon + 1) + "/" + String(currentTime->tm_year + 1900) + "</h3>";

    // Génération du bouton "Mettre à l'heure"
    page += "<button id='mettreAHeure' onclick='mettreAHeure()'>Mettre a l'heure</button>";

    // Ajouter un message d'avertissement si `heureAJour` est faux
    if (!heureAJour) {
        page += "<p class='alert'>Attention /!\\ il n'y a eu pas de mise a l'heure depuis le dernier reboot</p>";
    }

    // Formulaire pour les lignes d'arrosage
    page += "<form action=\"/submit\" method=\"POST\">";

    // Ligne 1
    page += "<h2>Ligne 1</h2>";
    page += "Actif: <input type=\"radio\" name=\"etat1\" value=\"1\"";
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
        int daysUntilNext = ligne1.frequence - (currentTime->tm_yday % ligne1.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne1.heure;
        nextWateringTime->tm_min = ligne1.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<p class='info'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</p>";
    }

    // Ligne 2
    page += "<h2>Ligne 2</h2>";
    page += "Actif: <input type=\"radio\" name=\"etat2\" value=\"1\"";
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
        int daysUntilNext = ligne2.frequence - (currentTime->tm_yday % ligne2.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne2.heure;
        nextWateringTime->tm_min = ligne2.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<p class='info'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</p>";
    }

    // Ligne 3
    page += "<h2>Ligne 3</h2>";
    page += "Actif: <input type=\"radio\" name=\"etat3\" value=\"1\"";
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
        int daysUntilNext = ligne3.frequence - (currentTime->tm_yday % ligne3.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne3.heure;
        nextWateringTime->tm_min = ligne3.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<p class='info'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</p>";
    }

    // Ligne 4
    page += "<h2>Ligne 4</h2>";
    page += "Actif: <input type=\"radio\" name=\"etat4\" value=\"1\"";
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
        int daysUntilNext = ligne4.frequence - (currentTime->tm_yday % ligne4.frequence);
        time_t nextWatering = now + (daysUntilNext * 86400);
        struct tm *nextWateringTime = localtime(&nextWatering);
        nextWateringTime->tm_hour = ligne4.heure;
        nextWateringTime->tm_min = ligne4.minute;
        nextWateringTime->tm_sec = 0;
        mktime(nextWateringTime);

        page += "<p class='info'>Prochain arrosage: ";
        page += String(nextWateringTime->tm_mday) + "/" + String(nextWateringTime->tm_mon + 1) + " a " +
                String(nextWateringTime->tm_hour) + ":" + (nextWateringTime->tm_min < 10 ? "0" : "") + String(nextWateringTime->tm_min);
        page += "</p>";
    }

    // Bouton de soumission pour toutes les lignes
    page += "<input type=\"submit\" value=\"Valider\">";
    page += "</form>";
    page += "</body></html>";

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
    //sauvegarderParametres();

     // Répondre à la demande
    server.send(200, "text/html", "<html><body><h1>Parametres mis a jour !</h1><a href=\"/\">Retour</a></body></html>");
}

void handleNotFound() {
    server.send(404, "text/plain", "Page non trouvee !");
}

//mise a l'heure
void handleSetTime() {
    if (server.hasArg("heure") && server.hasArg("minutes") && server.hasArg("secondes") &&
        server.hasArg("jour") && server.hasArg("mois") && server.hasArg("annee")) {

        int heure = server.arg("heure").toInt();
        int minutes = server.arg("minutes").toInt();
        int secondes = server.arg("secondes").toInt();
        int jour = server.arg("jour").toInt();
        int mois = server.arg("mois").toInt();
        int annee = server.arg("annee").toInt();

        struct tm tm;
        tm.tm_year = annee - 1900; // Les années sont comptées depuis 1900
        tm.tm_mon = mois - 1; // Les mois sont comptés de 0 à 11
        tm.tm_mday = jour;
        tm.tm_hour = heure;
        tm.tm_min = minutes;
        tm.tm_sec = secondes;
        time_t t = mktime(&tm);
        struct timeval now = { .tv_sec = t };
        settimeofday(&now, NULL);
        
        // Mettre à jour le drapeau `heureAJour`
        heureAJour = 1;

        // Répondre avec un message de confirmation et un bouton de retour
       server.send(200, "text/html", "<html><body><h1>Heure mise  jour !</h1><a href=\"/\">Retour</a></body></html>");
        
    } else {
        server.send(400, "text/plain", "Paramètres manquants");
    }
}


