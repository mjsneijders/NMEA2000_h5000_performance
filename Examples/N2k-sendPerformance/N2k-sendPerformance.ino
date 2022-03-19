#include <Arduino.h>
//#define N2k_CAN_INT_PIN 21

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <memory>
#include "Settings.h"
#include "webconfig.h"
cConfig Configdata;

#include "NMEA2000_CAN.h"  // This will automatically choose right CAN library and create suitable NMEA2000 object
#include "N2kMessages.h"
#include "N2kDataHandler.h"
#include "BoardSerialNumber.h"
#include "BoatData.h"


#include <Time.h>
#include <TimeLib.h>

tBoatData Boatdata;

#define DefaultSerialNumber 999999
uint32_t GetSerialNumber() {
  uint32_t Sno=GetBoardSerialNumber();

  return ( Sno!=0?Sno:DefaultSerialNumber );
}


WebServer webserver(80);


tN2kHandler N2kHandler(&NMEA2000);
const unsigned long TransmitMessages[] PROGMEM={126992L,126993L,127258L,129025L,129026L,129029L,129033L,129044L,129539L,129540L,130306L,130311L,130312L,130314L,130323L,0};

//  NMEA2000 object
void setup_can1(){
     NMEA2000.SetN2kCANSendFrameBufSize(150);
     NMEA2000.SetN2kCANReceiveFrameBufSize(150);
    char SnoStr[33];
    uint32_t SerialNumber=GetSerialNumber();
    snprintf(SnoStr,32,"%lu",(long unsigned int)SerialNumber);
    NMEA2000.SetProductInformation(SnoStr, // Manufacturer's Model serial code. 
                                     100, // Manufacturer's product code
                                     "Simple battery monitor",  // Manufacturer's Model ID
                                     "1.0.0.2 (2017-06-13)",  // Manufacturer's Software version code
                                     "1.0.0.0 (2017-06-13)", // Manufacturer's Model version
                                     0xff, // load equivalency - use default
                                     0xffff, // NMEA 2000 version - use default
                                     0xff, // Sertification level - use default
                                     0
                                     );
    // Set device information for temperature monitor
    NMEA2000.SetDeviceInformation(SerialNumber, // Unique number. Use e.g. Serial number.
                                  130, // Device function=Temperature. See codes on http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                  75, // Device class=Sensor Communication Interface. See codes on  http://www.nmea.org/Assets/20120726%20nmea%202000%20class%20&%20function%20codes%20v%202.00.pdf
                                  2040, // Just choosen free from code list on http://www.nmea.org/Assets/20121020%20nmea%202000%20registration%20list.pdf                               
                                  4, // Marine
                                  0
                                 );
    
    NMEA2000.SetForwardStream(&Serial);
    // NMEA2000.SetForwardType(tNMEA2000::fwdt_Text); // Show in clear text. Leave uncommented for default Actisense format.
    NMEA2000.SetMode(tNMEA2000::N2km_ListenAndNode,36);
    //NMEA2000.SetDebugMode(tNMEA2000::dm_Actisense); // Uncomment this, so you can test code without CAN bus chips on Arduino Mega
    NMEA2000.EnableForward(false); // Disable all msg forwarding to USB (=Serial)
    NMEA2000.ExtendTransmitMessages(TransmitMessages);
    NMEA2000.AttachMsgHandler(&N2kHandler);
    NMEA2000.Open();
}
void setup_boatdata(){
  Boatdata.Datetime.LastUpdate=N2kUInt32NA;
  Boatdata.Datetime.Systemtime=N2kUInt32NA;
  Boatdata.Datetime.Systemdate=N2kUInt32NA;
  
  Boatdata.Position.LastUpdate=N2kUInt32NA;

  Boatdata.Course.Water.LastUpdate=N2kUInt32NA;
  Boatdata.Course.Gps.LastUpdate=N2kUInt32NA;
  Boatdata.Course.Gps.Heading=N2kDoubleNA;
  Boatdata.Course.Compass.LastUpdate=N2kUInt32NA;
  Boatdata.Course.Variation=2; 
  Boatdata.Course.Deviation=0; 
  
  Boatdata.Navigation.BearingReference=N2khr_true;
  Boatdata.Navigation.CalculationType=N2kdct_RhumbLine;
  Boatdata.Navigation.XTEMode=N2kxtem_Autonomous; 


}
void setup_wifi(){
     String __ssid=Configdata.Wifi.ssid.get();
    char ssid[__ssid.length()+1];
    __ssid.toCharArray(ssid, __ssid.length()+1);
    String __password=Configdata.Wifi.password.get();
    char password[__password.length()+1]; 
    __password.toCharArray(password, __password.length()+1); 

  if (Configdata.Wifi.Mode.get() == 0){
        Serial.print ("Starting AP Wifi mode"); 
        WiFi.enableAP(true); 
        delay(100);
        IPAddress local_IP(Configdata.Wifi.ip1.get(),Configdata.Wifi.ip2.get(),Configdata.Wifi.ip3.get(),Configdata.Wifi.ip4.get());
        IPAddress subnet(255,255,255,0);
        Serial.print("Setting soft-AP configuration ... ");
        Serial.println(WiFi.softAPConfig(local_IP, local_IP, subnet) ? "Ready" : "Failed!");
        //WiFi.setTxPower(WIFI_POWER_7dBm);
        Serial.print("Setting soft-AP ... ");

        Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");
     //Serial.println((String) WiFi.getTxPower());
        Serial.print("Soft-AP IP address = ");
        Serial.println(WiFi.softAPIP());  
        Serial.println("done starting SoftAP"); 
  }else{
      Serial.print ("Starting Client Wifi mode\n");
      WiFi.mode(WIFI_STA);
      Serial.println (ssid); 
      Serial.println (password); 
      WiFi.begin(ssid,password);
      Serial.println("");
    
      // Wait for connection
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(Configdata.Wifi.ssid.get());
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
  } 
}

  


void setup() {
    
    Serial.begin(115200);
    Configdata.read();
    setup_can1(); 
    setup_boatdata();
    Configdata.print(); 
    setup_wifi(); 
    setupWebserver();
    Serial.println (" setup done!"); 
}

void loop() {
    NMEA2000.ParseMessages();
    N2kSendPerformance();
    webserver.handleClient();
}



#define PerformanceUpdatePeriod 1000
void N2kSendPerformance() {
  static unsigned long TimeUpdated=millis();
  static unsigned char SID=0; 
  tN2kMsg N2kMsg;
   if  (millis() - TimeUpdated >= PerformanceUpdatePeriod ){
    TimeUpdated=millis();
        // send Performancedate here
        //          SetN2kPGN127258(N2kMsg, SID,Boatdata.Heading.source,Boatdata.Datetime.DaysSince1970,DegToRad(Variation));
        if (NMEA2000.SendMsg(N2kMsg)){
             // blabla
        }
   }
   
}
