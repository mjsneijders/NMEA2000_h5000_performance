#ifndef _WEBCONFIG_H_
#define _WEBCONFIG_H_
#include <stdint.h>
#include <Arduino.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
#include <WebServer.h>
#include "Settings.h"

//String WebPageName; 

extern WebServer webserver;
extern cConfig Configdata;

bool is_authentified();
void handleLogin();
void handleLogout(); 
void startPage();
void wifiPage(); 
void sourcesPage();
void n2kPage();
void calculationsPage();
void adjustmentsPage();


void handleNotFound();
void setupWebserver();



String getStyle();
String getHead(String content);
String getFoot(String content = "" ); 
String pageAddTable(String content);
String pageAddRow(String content);
String pageAddValue(String content); 


String get8bit(uint8_t Number); 
String get16bit(uint16_t Number); 
String get32bit(uint32_t Number); 
String getdouble(double Number); 


#endif
