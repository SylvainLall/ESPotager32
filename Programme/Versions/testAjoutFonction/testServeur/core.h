#ifndef CORE_H
#define CORE_H


extern const char* ssid;
extern const char* password;



void initWiFi();                //serveurWeb.cpp
void initServer();              //serveurWeb.cpp
void handleClient();            //serveurWeb.cpp
#endif // CORE_H