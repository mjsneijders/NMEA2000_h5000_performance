#include "Settings.h"
#include <Arduino.h>
#include <Preferences.h>
#include <Esp.h>


#define RESETPIN 23
#define RESETCHECK 5000

Preferences preferences;
//string variable
cSTRING::cSTRING(){
   _data=""; 
}
void  cSTRING::set(String data){
    _data=data; 
}  
String cSTRING::get(){ 
    return _data;
}
void cSTRING::name(char *str){
  _name=str; 
}
void cSTRING::namespc(char *str){
  _namespc=str; 
}
void cSTRING::read(){
    preferences.begin(_namespc, true); 
    _data = preferences.getString( _name, "" );
    preferences.end();
}
void cSTRING::write(){
    preferences.begin(_namespc, false); 
    preferences.putString( _name, _data);
    preferences.end();
}
void cSTRING::print(){
    Serial.println((String)_namespc + "." + _name + " = " + _data); 
}

//bool variable
cBOOL::cBOOL(){
   _data=false; 
}
void  cBOOL::set(bool data){
    _data=data; 
}  
bool cBOOL::get(){ 
    return _data;
}
void cBOOL::name(char *str){
  _name=str; 
}
void cBOOL::namespc(char *str){
  _namespc=str; 
}
void cBOOL::read(){
    preferences.begin(_namespc, true); 
    _data = preferences.getBool( _name, 0);
    preferences.end();
}
void cBOOL::write(){
    preferences.begin(_namespc, false); 
    preferences.putBool( _name, _data);
    preferences.end();
}
void cBOOL::print(){
    Serial.println((String)_namespc + "." + _name + " = " + _data); 
}

//uin8_t variable
cUINT8::cUINT8(){
   _data=0; 
}
void  cUINT8::set(uint8_t data){
    _data=data; 
}  
uint8_t cUINT8::get(){ 
    return _data;
}
void cUINT8::name(char *str){
  _name=str; 
}
void cUINT8::namespc(char *str){
  _namespc=str; 
}
void cUINT8::read(){
    preferences.begin(_namespc, true); 
    _data = preferences.getUChar( _name, 0);
    preferences.end();
}
void cUINT8::write(){
    preferences.begin(_namespc, false); 
    preferences.putUChar( _name, _data);
    preferences.end();
}
void cUINT8::print(){
    Serial.println((String)_namespc + "." + _name + " = " + _data); 
}

//uin16_t variable
cUINT16::cUINT16(){
   _data=0; 
}
void  cUINT16::set(uint16_t data){
    _data=data; 
}  
uint16_t cUINT16::get(){ 
    return _data;
}
void cUINT16::name(char *str){
  _name=str; 
}
void cUINT16::namespc(char *str){
  _namespc=str; 
}
void cUINT16::read(){
    preferences.begin(_namespc, true); 
    _data = preferences.getUShort( _name, 0);
    preferences.end();
}
void cUINT16::write(){
    preferences.begin(_namespc, false); 
    preferences.putUShort( _name, _data);
    preferences.end();
}
void cUINT16::print(){
    Serial.println((String)_namespc + "." + _name + " = " + _data); 
}


//uin32_t variable
cUINT32::cUINT32(){
   _data=0; 
}
void  cUINT32::set(uint32_t data){
    _data=data; 
}  
uint32_t cUINT32::get(){ 
    return _data;
}
void cUINT32::name(char *str){
  _name=str; 
}
void cUINT32::namespc(char *str){
  _namespc=str; 
}
void cUINT32::read(){
    preferences.begin(_namespc, true); 
    _data = preferences.getULong( _name, 0);
    preferences.end();
}
void cUINT32::write(){
    preferences.begin(_namespc, false); 
    preferences.putULong( _name, _data);
    preferences.end();
}
void cUINT32::print(){
    Serial.println((String)_namespc + "." + _name + " = " + _data); 
}

//double variable
cDOUBLE::cDOUBLE(){
   _data=0; 
}
void  cDOUBLE::set(double data){
    _data=data; 
}  
double cDOUBLE::get(){ 
    return _data;
}
void cDOUBLE::name(char *str){
  _name=str; 
}
void cDOUBLE::namespc(char *str){
  _namespc=str; 
}
void cDOUBLE::read(){
    preferences.begin(_namespc, true); 
    _data = preferences.getDouble( _name, 0);
    preferences.end();
}
void cDOUBLE::write(){
    preferences.begin(_namespc, false); 
    preferences.putDouble( _name, _data);
    preferences.end();
}
void cDOUBLE::print(){
    Serial.println((String)_namespc + "." + _name + " = " + _data); 
}


//Wificonfig
cWifiConfig::cWifiConfig(){
      Mode.name("Mode"); 
      Mode.namespc("Wifi"); 
      ssid.name("ssid");
      ssid.namespc("Wifi");
      password.name("password");
      password.namespc("Wifi");
      ip1.name("ip1");
      ip1.namespc("Wifi");
      ip2.name("ip2");
      ip2.namespc("Wifi");
      ip3.name("ip3");
      ip3.namespc("Wifi");
      ip4.name("ip4");
      ip4.namespc("Wifi");
      this->print(); 
}  
void cWifiConfig::read(){
      Mode.read(); 
      ssid.read();
      password.read();
      ip1.read();
      ip2.read();
      ip3.read();
      ip4.read();
}
void cWifiConfig::write(){
      Mode.write(); 
      ssid.write(); 
      password.write(); 
      ip1.write(); 
      ip2.write(); 
      ip3.write(); 
      ip4.write(); 
}
void cWifiConfig::print(){
      Mode.print(); 
      ssid.print(); 
      password.print(); 
      ip1.print(); 
      ip2.print(); 
      ip3.print(); 
      ip4.print(); 
}
//SourcesConfig
cSourcesConfig::cSourcesConfig(){
      Gps.name("Gps");
      Gps.namespc("Sources"); 
      Water.name("Waterspeed");
      Water.namespc("Sources");
      Compass.name("Compass");
      Compass.namespc("Sources");
      Wind.name("Wind");
      Wind.namespc("Sources");
      Variation.name("Variation"); 
      Variation.namespc("Sources"); 
      
}
void cSourcesConfig::read(){
      Gps.read();
      Water.read();
      Compass.read();
      Wind.read();
      Variation.read(); 
}
void cSourcesConfig::write(){
      Gps.write();
      Water.write();
      Compass.write();
      Wind.write();
      Variation.write(); 
}
void cSourcesConfig::print(){
      Gps.print();
      Water.print();
      Compass.print();
      Wind.print();
	  Variation.print(); 
}
//Nmea2000config
cNmea2000Config::cNmea2000Config(){
      Name.name("Name"); 
      Name.namespc("Nmea2000"); 
      Address.name("Address"); 
      Address.namespc("Nmea2000"); 
}
void cNmea2000Config::read(){
      Name.read(); 
      Address.read();
}
void cNmea2000Config::write(){
      Name.write(); 
      Address.write();  
}
void cNmea2000Config::print(){
      Name.print(); 
      Address.print();  
}
// Deviceconfig
    cDeviceConfig::cDeviceConfig(){
      Password.name("Password"); 
      Password.namespc("Device");
      Checkvalue.name("Checkvalue"); 
      Checkvalue.namespc("Device"); 
    }
    void cDeviceConfig::read(){
      Password.read(); 
      Checkvalue.read(); 
    }
    void cDeviceConfig::write(){
      Password.write(); 
      Checkvalue.write(); 
    }
    void cDeviceConfig::print(){
      Password.print(); 
       Checkvalue.print(); 
    }
// Calculationsconfig
    cCalculationsConfig::cCalculationsConfig(){
      CalculateVariation.name("Calculate Variation"); 
      CalculateVariation.namespc("Calculation");
      SendVariation.name("Send Variation"); 
      SendVariation.namespc("Calculation"); 
	  CalculateTrueWind.name("Calculate TrueWind"); 
      CalculateTrueWind.namespc("Calculation");
      SendTrueWind.name("Send TrueWind"); 
      SendTrueWind.namespc("Calculation"); 
	  CalculateTide.name("Calculate Tide"); 
      CalculateTide.namespc("Calculation");
      SendTide.name("Send Tide"); 
      SendTide.namespc("Calculation"); 
    }
    void cCalculationsConfig::read(){
      CalculateVariation.read(); 
      SendVariation.read(); 
	  CalculateTrueWind.read(); 
      SendTrueWind.read(); 
	  CalculateTide.read(); 
      SendTide.read(); 
    }
    void cCalculationsConfig::write(){
      CalculateVariation.write(); 
      SendVariation.write(); 
	  CalculateTrueWind.write(); 
      SendTrueWind.write();
	  CalculateTide.write(); 
      SendTide.write();
    }
    void cCalculationsConfig::print(){
      CalculateVariation.print(); 
      SendVariation.print(); 
	  CalculateTrueWind.print(); 
      SendTrueWind.print(); 
	  CalculateTide.print(); 
      SendTide.print(); 
    }
// Adjustmentsconfig
    cAdjustmentsConfig::cAdjustmentsConfig(){
      WaterSpeed.name("Waterspeed"); 
      WaterSpeed.namespc("Adjustments");
      LeeWay.name("LeeWay"); 
      LeeWay.namespc("Adjustments"); 
    }
    void cAdjustmentsConfig::read(){
      WaterSpeed.read(); 
      LeeWay.read(); 
    }
    void cAdjustmentsConfig::write(){
      WaterSpeed.write(); 
      LeeWay.write(); 
    }
    void cAdjustmentsConfig::print(){
      WaterSpeed.print(); 
      LeeWay.print(); 
    }




//Config
  void cConfig::read(){
      Wifi.read(); 
      Sources.read(); 
      Nmea2000.read();
	  Calculation.read(); 
	  Adjustments.read(); 
      Device.read(); 
      this->resetcheck(); 
      if ( Device.Checkvalue.get() != RESETCHECK ){
        Serial.println("stored check value invalid,  restoring all defaults");
        this->defaults();
        this->write(); 
      }
    
  }
  void cConfig::write(){
      Wifi.write(); 
      Sources.write(); 
      Nmea2000.write();
	  Calculation.write(); 
	  Adjustments.write(); 
      Device.write(); 
  }
   void cConfig::print(){
      Wifi.print(); 
      Sources.print(); 
      Nmea2000.print();
	  Calculation.print(); 
	  Adjustments.print(); 
      Device.print(); 
  }
  void cConfig::defaults(){
		Wifi.Mode.set(0); 
		Wifi.ssid.set("N2K Performance Computer");
		Wifi.password.set("password"); 
		Wifi.ip1.set(192); 
		Wifi.ip2.set(168); 
		Wifi.ip3.set(179);
		Wifi.ip4.set(1);
		Sources.Gps.set(255); 
		Sources.Water.set(255); 
		Sources.Compass.set(255); 
		Sources.Wind.set(255);
		Sources.Variation.set(255);
		Nmea2000.Name.set("N2K H5000"); 
		Nmea2000.Address.set(73); 
		Calculation.CalculateVariation.set(false); 
		Calculation.SendVariation.set(false); 
		Calculation.CalculateTrueWind.set(false); 
		Calculation.SendTrueWind.set(false); 
		Calculation.CalculateTide.set(false); 
		Calculation.SendTide.set(false); 
		Adjustments.WaterSpeed.set(0);
		Adjustments.LeeWay.set(0); 
		Device.Password.set("password"); 
		Device.Checkvalue.set(RESETCHECK);
   }
   void cConfig::resetcheck(){
        pinMode(RESETPIN,INPUT);
        if (digitalRead(RESETPIN) == 1){
            Serial.print ("**********************************************\nStarting with Factory Defaults \n**********************************************\n");
            this->defaults();  
            this->write ();
            delay (10000); 
            ESP.restart();
        }
  }
