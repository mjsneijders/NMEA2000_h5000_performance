#ifndef _BoatData_H_
#define _BoatData_H_

#include <N2kMessages.h>
struct tBoatData {
  struct tBDdatetime {
    uint32_t LastUpdate; 
    uint16_t Systemdate;
    double Systemtime;
    tN2kTimeSource Source; 
    uint16_t DaysSince1970;
    double SecondsSinceMidnight;
  };

  struct tBDposition {
    uint32_t LastUpdate; 
    double Latitude;
    double Longitude; 
    double Altitude;
    tN2kGNSStype GNSStype; 
    tN2kGNSSmethod GNSSmethod;
    unsigned char nSatellites; 
    double HDOP; 
    double PDOP; 
    double GeoidalSeparation;
    unsigned char nReferenceStations; 
    tN2kGNSStype ReferenceStationType; 
    uint16_t ReferenceSationID;
    double AgeOfCorrection;
  };
    struct tBDSpeedHeading {
    uint32_t LastUpdate; 
    double Speed; 
    double Heading; 
  };
  struct tBDCourse {
    uint32_t LastUpdate; 
    double Variation;
    double Deviation;
    tBDSpeedHeading Water; 
    tBDSpeedHeading Gps; 
    tBDSpeedHeading Compass; 
  };
  struct tBDWind{
      uint32_t Lastupdate;
      double Speed; 
      double Angle; 
      double Direction; 
    };
  struct tBDWeather{
    tBDWind TrueWind;
    tBDWind AppWind;
  };

  struct tBDnavigation {
    uint32_t Lastupdate;
    double DistanceToWaypoint;
    tN2kHeadingReference BearingReference;
    bool PerpendicularCrossed;
    bool ArrivalCircleEntered;
    tN2kDistanceCalculationType CalculationType;
    double ETATime;
    int16_t ETADate;
    double BearingOriginToDestinationWaypoint; 
    double BearingPositionToDestinationWaypoint;
    uint8_t OriginWaypointNumber;
    uint8_t DestinationWaypointNumber;
    double DestinationLatitude;
    double DestinationLongitude;
    double WaypointClosingVelocity;
    tN2kXTEMode XTEMode;
    bool NavigationTerminated;
    double XTE;
  };

  uint32_t Lastupdate;
  tBDposition Position; 
  tBDdatetime Datetime; 
  tBDnavigation Navigation;
  tBDCourse Course; 
  tBDWeather Weather; 

};

extern tBoatData Boatdata;
#endif // _BoatData_H_
