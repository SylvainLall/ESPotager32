#include "core.h"
#include <Arduino.h>
#include <NewPing.h>

void  setupMesure() {
#define MAX_DISTANCE 200 //  exclu toutes mesures superieur a cette valeur.  valeur distance max du capteur : 500cm
#define PING_MEDIAN_DELAY 30000
#define NO_ECHO 0


const int distanceSensorTrigPin = D6;
const int distanceSensorEchoPin = D5;
const float niveauCuveMax = 20; // mesure du niveau maximum de la cuve en cm (niveauEau capteur niveau max)
const float niveauCuveMin = 165; // mesure du niveau minimum de la cuve en cm (niveauEau capteur niveau min)
const float hauteurCuve = niveauCuveMin - niveauCuveMax;
long niveauEau = 0;
int niveauPourcent; // niveau de l'eau en %

NewPing sonar(distanceSensorTrigPin, distanceSensorEchoPin, MAX_DISTANCE);
}
void mesureNiveau() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  long distanceEcho = sonar.ping_median(40);
  niveauEau = sonar.convert_cm(distanceEcho);
  //niveauPourcent = (1-((niveauEau - niveauCuveMax)/hauteurCuve));
  niveauPourcent = (1 - (( niveauEau - niveauCuveMax) / hauteurCuve)) * 100;


  //Serial.print(" Temperature: ");
  //Serial.print(temp);
  //Serial.print(" niveauEau: ");
  //Serial.println(niveauEau);
  Serial.print(niveauPourcent);
  Serial.println("%");

}