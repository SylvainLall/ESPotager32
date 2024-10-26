#include "core.h"
#include <time.h>  // Pour les timestamps
#include <Arduino.h>

// Buffer circulaire pour stocker 10 logs
const int MAX_LOGS = 10;
String logBuffer[MAX_LOGS];
int logIndex = 0;
int logCount = 0;

// Fonction pour ajouter une entrée de log
void ajouterLog(const String &message) {
    time_t now = time(nullptr);
    struct tm *currentTime = localtime(&now);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%d/%m/%y %H:%M:%S", currentTime);

    // Créer l'entrée log avec le timestamp
    String logEntry = String(timestamp) + " - " + message;

    // Ajouter au buffer circulaire
    logBuffer[logIndex] = logEntry;
    logIndex = (logIndex + 1) % MAX_LOGS;
    if (logCount < MAX_LOGS) {
        logCount++;
    }
}

// Fonction pour récupérer les logs sous forme de String
String obtenirLogs() {
    String logs = "";
    for (int i = 0; i < logCount; i++) {
        int index = (logIndex + i) % MAX_LOGS;
        logs += logBuffer[index] + "\n";
    }
    return logs;
}
