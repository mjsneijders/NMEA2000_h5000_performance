#include "N2kDataHandler.h"
#include <N2kMessages.h>
#include <math.h>
#include "BoatData.h"
#include "Settings.h"
extern tNMEA2000 &NMEA2000;
extern tBoatData Boatdata; 
extern cConfig Configdata;


void tN2kHandler::HandleMsg(const tN2kMsg &N2kMsg) {
  switch (N2kMsg.PGN) {
    case 127250UL: HandleHeading(N2kMsg);break;         //Heading
    case 127258UL: HandleVariation(N2kMsg); break;      //Variation
    case 129025UL: HandlePosition(N2kMsg); break;       //GPS position, Rapid Update
    case 129026UL: HandleCOGSOG(N2kMsg);break;          //GPS COG&SOG, Rapid Update
    case 129029UL: HandleGNSS(N2kMsg);break;            //GPS GNSS Position data
    case 128259UL: HandleBoatSpeed(N2kMsg);break;       //Boat speed (STW)
    case 130306UL: HandleWind(N2kMsg);break;            //Wind data
    default: ;break;
  }
}

void tN2kHandler::HandleHeading(const tN2kMsg &N2kMsg) {
  if ( N2kMsg.Source == Configdata.Sources.Compass.get() || Configdata.Sources.Compass.get() == 255 ){ 
          unsigned char SID;
          tN2kHeadingReference ref;
          double _Deviation = 0;
          double _Variation;
          double _Heading; 
        
          if ( ParseN2kHeading(N2kMsg, SID, _Heading, _Deviation, _Variation, ref) ) {
                if ( ref == N2khr_magnetic ) {
                        Boatdata.Course.Compass.LastUpdate = millis();
                        Boatdata.Course.Compass.Heading=_Heading + Boatdata.Course.Variation + Boatdata.Course.Deviation;
                }
                if ( ref == N2khr_true ) {
                        Boatdata.Course.Compass.LastUpdate = millis();
                        Boatdata.Course.Compass.Heading=_Heading;  
                }    
          }
  }
}
void tN2kHandler::HandleBoatSpeed(const tN2kMsg &N2kMsg) {
  if ( N2kMsg.Source == Configdata.Sources.Water.get() || Configdata.Sources.Water.get() == 255 ){

          unsigned char SID;
          double WaterReferenced;
          double GroundReferenced;
          tN2kSpeedWaterReferenceType SWRT;
            if ( ParseN2kBoatSpeed(N2kMsg,SID,WaterReferenced,GroundReferenced,SWRT) ) {
                      Boatdata.Course.Water.LastUpdate = millis();
                      Boatdata.Course.Water.Speed=WaterReferenced + Configdata.Adjustments.WaterSpeed.get() ;
            }
  }
}
void tN2kHandler::HandleCOGSOG(const tN2kMsg &N2kMsg) {
    if ( N2kMsg.Source == Configdata.Sources.Gps.get() || Configdata.Sources.Gps.get() == 255 ){
        unsigned char SID;
        tN2kHeadingReference HeadingReference;
          if ( ParseN2kCOGSOGRapid(N2kMsg,
                                   SID,
                                   HeadingReference,
                                   Boatdata.Course.Gps.Heading,
                                   Boatdata.Course.Gps.Speed
             )) {
                 
                    Boatdata.Course.Gps.LastUpdate=millis();
                    if ( HeadingReference==N2khr_magnetic ) {
                      Boatdata.Course.Gps.Heading+=Boatdata.Course.Variation;
                    }
          }
    }
}
void tN2kHandler::HandleWind(const tN2kMsg &N2kMsg) {
  if ( N2kMsg.Source == Configdata.Sources.Wind.get() || Configdata.Sources.Wind.get() == 255 ){
      unsigned char SID;
      tN2kWindReference WindReference;
      double Heading; 
      double WindSpeed, WindAngle; 
      double TWS, TWA, TWD;
      double SOG, COG; 
    
      if ( ParseN2kWindSpeed(N2kMsg, SID, WindSpeed, WindAngle, WindReference) ) {
        if ( WindReference == N2kWind_Apparent ){
              Boatdata.Weather.AppWind.Lastupdate=millis();
              Boatdata.Weather.AppWind.Speed=WindSpeed; 
              Boatdata.Weather.AppWind.Angle=WindAngle;
              Boatdata.Weather.AppWind.Direction=Boatdata.Course.Compass.Heading + WindAngle;
              
              if ( Configdata.Calculation.CalculateTrueWind.get()== true ){
                  
                    if (millis() - Boatdata.Course.Compass.LastUpdate< 1500 && Boatdata.Course.Compass.LastUpdate != N2kUInt32NA ){
                      Heading=Boatdata.Course.Compass.Heading; 
                    }else if (millis() - Boatdata.Course.Gps.LastUpdate< 1500 && Boatdata.Course.Gps.LastUpdate != N2kUInt32NA ){
                      Heading=Boatdata.Course.Gps.Heading;
                    }else{
                      return; 
                    }
                    
                    if (millis() - Boatdata.Course.Gps.LastUpdate< 1500 && Boatdata.Course.Gps.LastUpdate != N2kUInt32NA) {
                        SOG=Boatdata.Course.Gps.Heading;
                        COG=Boatdata.Course.Gps.Heading;
           
                        CalculateTruewind(Heading, 
                                          SOG, 
                                          COG, 
                                          WindSpeed, 
                                          WindAngle, 
                                          TWS, 
                                          TWD, 
                                          TWA);
                        Boatdata.Weather.TrueWind.Lastupdate=millis();
                        Boatdata.Weather.TrueWind.Speed=TWS; 
                        Boatdata.Weather.TrueWind.Direction=TWD;
                        Boatdata.Weather.TrueWind.Direction=TWA;
                        if ( Configdata.Calculation.SendTrueWind.get()== true ){
                              tN2kMsg N2kMsg_1;
                              //*//TWD
                              SetN2kWindSpeed (N2kMsg_1, 1, TWS, TWD, N2kWind_True_North); 
                              NMEA2000.SendMsg(N2kMsg_1); 
                              //*
                              //*//TWA
                              SetN2kWindSpeed (N2kMsg_1, 1, TWS, TWA, N2kWind_True_boat);                           
                              NMEA2000.SendMsg(N2kMsg_1);
                        }
                    }
              }
         }else if ( WindReference == N2kWind_True_North ){
          //*//TWD
              if ( Configdata.Calculation.CalculateTrueWind.get()== false )
                    Boatdata.Weather.TrueWind.Lastupdate=millis();
                    Boatdata.Weather.TrueWind.Speed=WindSpeed; 
                    Boatdata.Weather.TrueWind.Direction=WindAngle;
         }else if ( WindReference == N2kWind_True_boat ){
          //*//TWA
              if ( Configdata.Calculation.CalculateTrueWind.get()== false )
                    Boatdata.Weather.TrueWind.Lastupdate=millis();
                    Boatdata.Weather.TrueWind.Speed=WindSpeed; 
                    Boatdata.Weather.TrueWind.Angle=WindAngle;
         }
      }
}
}
void tN2kHandler::HandlePosition(const tN2kMsg &N2kMsg) {
    if ( N2kMsg.Source == Configdata.Sources.Gps.get() || Configdata.Sources.Gps.get() == 255 ){ 
          if ( ParseN2kPGN129025(N2kMsg,
                                 Boatdata.Position.Latitude, 
                                 Boatdata.Position.Longitude
              )) {
                  Boatdata.Position.LastUpdate=millis();
              }
     }
}
void tN2kHandler::HandleGNSS(const tN2kMsg &N2kMsg) {
       if ( N2kMsg.Source == Configdata.Sources.Gps.get() || Configdata.Sources.Gps.get() == 255 ){ 
            unsigned char SID;
              if ( ParseN2kGNSS(N2kMsg,
                                SID,
                                Boatdata.Datetime.DaysSince1970,
                                Boatdata.Datetime.SecondsSinceMidnight,
                                Boatdata.Position.Latitude,
                                Boatdata.Position.Longitude,
                                Boatdata.Position.Altitude,
                                Boatdata.Position.GNSStype,
                                Boatdata.Position.GNSSmethod,
                                Boatdata.Position.nSatellites,
                                Boatdata.Position.HDOP,
                                Boatdata.Position.PDOP,
                                Boatdata.Position.GeoidalSeparation,
                                Boatdata.Position.nReferenceStations,
                                Boatdata.Position.ReferenceStationType,
                                Boatdata.Position.ReferenceSationID,
                                Boatdata.Position.AgeOfCorrection    
                  )) {
                if ( Boatdata.Datetime.DaysSince1970 > 17553){
                    Boatdata.Position.LastUpdate=millis();
                }
              }
       }
}
void tN2kHandler::HandleVariation(const tN2kMsg &N2kMsg) {
   if ( N2kMsg.Source == Configdata.Sources.Variation.get() || Configdata.Sources.Variation.get() == 255 ){ 
        unsigned char SID;
        tN2kMagneticVariation source; 
        uint16_t DaysSince1970; 
        if (ParseN2kMagneticVariation(N2kMsg,SID,source, DaysSince1970, Boatdata.Course.Variation)){
              Boatdata.Course.LastUpdate=millis(); 
        }
   }
}

void tN2kHandler::CalculateTruewind(double Heading, double SOG, double COG, double AWS, double AWA, double &TWS, double &TWD, double &TWA){
/*/
input ONLY m/s for speeds and ONLY radials for angles. 
function takes 228 microSeconds on arduino Due. 

Include math.h for M_PI, sin(), cos() and atan2() functions

Input Variables: 
Heading = Compass heading ( prefereably TRUE,  but Magnetic should be okay if the display also uses Magnetic)
SOG = Speed over Ground from GPS (m/s)
COG = Course over Ground from GPS (radials)
AWS = Appearant Wind Speed from Wind device (m/s).
AWA = Appearant Wind Angle from wind device, relative to ship centerline. (radials)
Output Variables: 
TWS = Theoretical Wind Speed (m/s)
TWD = Theoretical Wind Direction, relative to north (radials)
TWA = Theoretical Wind Angle, relative to ship centerline (radials)

//*/

//force AWA into +/-pi radials  not 0-2pi radials.
while (AWA > M_PI) AWA -=2*  M_PI; 

//create AWD from Heading,  and fix into 0-2pi radials.
double AWD; 
AWD=Heading + AWA; 
while (AWD < 0 ) AWD += 2* M_PI; 
while (AWD > 2*M_PI ) AWD -= 2* M_PI;


//create boat vector(x,y) from SOG and COG.
double Xboat, Yboat; 
Xboat = sin(COG) * SOG; 
Yboat = cos(COG) * SOG; 

//create wind vector(x,y) from AWD and AWS.
double Xwind, Ywind;
Xwind=sin(AWD) * AWS; 
Ywind=cos(AWD) * AWS; 

//substract boat vector from wind vector to create Truewind Vector. 
double Xtw, Ytw; 
Xtw=Xwind-Xboat;
Ytw=Ywind-Yboat; 

//Calculate lenght of Truewindvector for Truewind Speed.
TWS = sqrt ((Xtw*Xtw) + (Ytw*Ytw)); 

//Calculate Angle of Truewindvector for Truewind direction. 
TWD = atan2 ( Xtw, Ytw); 

//make sure result is 0-2pi radials
while(TWD > (2* M_PI)) TWD -= 2* M_PI; 
while(TWD < 0) TWD += 2* M_PI;

//substract Heading for TrueWind Angle.
TWA = TWD - Heading; 

//for TWA  force 0-2pi radials
while(TWA > (2* M_PI)) TWA -= 2* M_PI; 
while (TWA < 0) TWA += 2*M_PI; 

}
