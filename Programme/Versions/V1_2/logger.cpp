#include "core.h"
#include <time.h> // Pour les timestamps

// Déclaration d'un tableau circulaire de logs
struct Log {
    String timestamp;
    String message;
};

Log logs[20];
int logIndex = 0; // Prochain index de log

// Fonction pour obtenir le timestamp actuel sous forme de chaîne
String getTimestamp() {
    time_t now = time(nullptr);
    struct tm *timeInfo = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", timeInfo);
    return String(buffer);
}

// Ajoute un log au tableau circulaire
void ajouterLog(const String &message) {
    logs[logIndex].timestamp = getTimestamp();
    logs[logIndex].message = message;
    logIndex = (logIndex + 1) % 20; // Incrémente et retourne à 0 quand on atteint 20 logs
}

// Génère la page HTML des logs
String genererPageLog() {
       String page = "<html><head><title>Logs du Systeme</title>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; margin: 0; padding: 0; }";
    page += ".back-btn {";
    page += "  background-color: #4CAF50;"; // Couleur de fond
    page += "  color: white;"; // Couleur du texte
    page += "  padding: 15px 32px;"; // Rembourrage
    page += "  text-align: center;"; // Centrer le texte
    page += "  text-decoration: none;"; // Pas de soulignement
    page += "  display: inline-block;"; // Alignement en ligne
    page += "  font-size: 16px;"; // Taille de police
    page += "  margin: 4px 2px;"; // Marges
    page += "  cursor: pointer;"; // Curseur pointer
    page += "  border: none;"; // Pas de bordure
    page += "  border-radius: 4px;"; // Coins arrondis
    page += "}";
    page += "h2 { font-size: 150%; }";  // Titre un peu plus grand
    page += "ul { font-size: 120%; }"; // Taille de la liste des logs en pourcentage
    page += "li { margin: 5px 0; }";   // Espacement entre les éléments de la liste
    page += "</style></head><body>";
    page += "<h2>Historique des Logs</h2><ul>";

    for (int i = 0; i < 20; i++) {
        int index = (logIndex + i) % 20; // Affichage circulaire
        if (!logs[index].timestamp.isEmpty()) { // Vérifie que le log n'est pas vide
            page += "<li>" + logs[index].timestamp + " - " + logs[index].message + "</li>";
        }
    }

    //page += "</ul><a href='/'>Retour a l'accueil</a></body></html>";
 
     page += "<button class='back-btn' onclick=\"window.location.href='/'\">Retour</button>";
   
    return page;
}

// Initialisation de la route pour afficher les logs
void initLogSystem(WebServer &server) {
    server.on("/log", HTTP_GET, [&server]() {
        server.send(200, "text/html", genererPageLog());
    });
}

/*pour info   
//bouton de redirection vers la page de log a mettre sur le serveur web : 
 page += "<style>";
    page += "body { font-family: Arial, sans-serif; margin: 0; padding: 0; }";
    page += ".log-btn { position: absolute; top: 10px; right: 10px; padding: 10px 20px; background-color: #808080; color: white; border: none; border-radius: 4px; cursor: pointer; }";
    page += "</style></head><body>";
    page += "<button class='log-btn' onclick=\"window.location.href='/log'\">Log</button>";
    */