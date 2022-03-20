#ifndef _SETTINGS_H_
#define _SETTINGS_H_
#include <Arduino.h>

#include <stdint.h>


class cSTRING{
public:
  cSTRING();
  void set(String);
  String get();
  void write();   
  void read();
  void name(char *str);
  void print();   
  void namespc(char *str);
private:
  String _data; 
  char *_name; 
  char *_namespc;
};
class cBOOL{
public:
  cBOOL();
  void set(bool);
  bool get();
  void write();   
  void read();
  void name(char *str);  
  void namespc(char *str);
    void print(); 
private:
  bool _data; 
  char *_name; 
  char *_namespc;
};
class cUINT8{
public:
  cUINT8();
  void set(uint8_t);
  uint8_t get();
  void write();   
  void read();
  void name(char *str);  
  void namespc(char *str);
    void print(); 
private:
  uint8_t _data; 
  char *_name; 
  char *_namespc;
};
class cUINT16{
public:
  cUINT16();
  void set(uint16_t);
  uint16_t get();
  void write();   
  void read();
  void name(char *str);  
  void namespc(char *str);
    void print(); 
private:
  uint16_t _data; 
  char *_name; 
  char *_namespc;
};
class cUINT32{
public:
  cUINT32();
  void set(uint32_t);
  uint32_t get();
  void write();   
  void read();
  void name(char *str);  
  void namespc(char *str);
    void print(); 
private:
  uint32_t _data; 
  char *_name; 
  char *_namespc;
};
class cDOUBLE{
public:
  cDOUBLE();
  void set(double);
  double get();
  void write();   
  void read();
  void name(char *str);  
  void namespc(char *str);
    void print(); 
private:
  double _data; 
  char *_name; 
  char *_namespc;
};

class cWifiConfig{
public: 
  cWifiConfig();
  cUINT8 Mode;
  cSTRING ssid;
  cSTRING password;
  cUINT8 ip1;
  cUINT8 ip2;
  cUINT8 ip3;
  cUINT8 ip4;
  void read();
  void write();
  void print();
};
class cSourcesConfig{
public: 
  cSourcesConfig();
  cUINT8 Gps;
  cUINT8 Water;
  cUINT8 Compass;
  cUINT8 Wind;
  cUINT8 Variation; 
  void read();
  void write();
  void print();
};
class cNmea2000Config{
public: 
  cNmea2000Config();
  cSTRING Name; 
  cUINT8 Address;
  void read();
  void write();
  void print();
};
class cDeviceConfig{
public: 
  cDeviceConfig();
  cSTRING Password; 
  cUINT16 Checkvalue;
  cDOUBLE Variation;  
  void read();
  void write();
  void print();
};
class cCalculationsConfig{
public: 
  cCalculationsConfig();
  cBOOL CalculateVariation; 
  cBOOL SendVariation; 
  cBOOL CalculateTrueWind; 
  cBOOL SendTrueWind; 
  cBOOL CalculateTide; 
  cBOOL SendTide; 
  void read();
  void write();
  void print();
};
class cAdjustmentsConfig{
public: 
  cAdjustmentsConfig();
  cDOUBLE WaterSpeed; 
  cDOUBLE LeeWay; 
  void read();
  void write();
  void print();
};

class cConfig{
public:
  cWifiConfig Wifi;
  cSourcesConfig Sources;
  cNmea2000Config Nmea2000; 
  cDeviceConfig Device;
  cCalculationsConfig Calculation; 
  cAdjustmentsConfig Adjustments;
  void defaults(); 
  void read();
  void write(); 
  void print();
  void resetcheck(); 
};


















#endif
