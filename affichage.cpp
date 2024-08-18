#include "core.h"
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void setupAffichage() {
  lcd.init();                      // Initialiser le LCD
  lcd.backlight();                 // Allumer le rétroéclairage
  lcd.clear();                     // Effacer l'affichage
}

void afficherNiveau() {
  lcd.clear();                     // Effacer l'écran

  // Afficher le pourcentage sur la première ligne
  lcd.setCursor(0, 0);             // Positionner le curseur sur la première ligne
  lcd.print("Niveau: ");           // Afficher "Niveau: "
  lcd.print(niveauPourcent);       // Afficher le pourcentage
  lcd.print("%");                  // Afficher le symbole pourcentage

  // Dessiner la barre de progression sur la deuxième ligne
  lcd.setCursor(0, 1);             // Positionner le curseur sur la deuxième ligne
  int barLength = map(niveauPourcent, 0, 100, 0, 16);  // Calculer la longueur de la barre
  for (int i = 0; i < barLength; i++) {
    lcd.print("|");                // Afficher un caractère pour chaque unité de la barre
  }
}