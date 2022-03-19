#include <NMEA2000.h>


class tN2kHandler : public tNMEA2000::tMsgHandler {


protected:
  void HandleWind(const tN2kMsg &N2kMsg); // 130306
  void HandlePosition(const tN2kMsg &N2kMsg);//129025
  void HandleCOGSOG(const tN2kMsg &N2kMsg); //129026
  void HandleGNSS(const tN2kMsg &N2kMsg); //129029
  void HandleHeading(const tN2kMsg &N2kMsg); //127250
  void HandleVariation(const tN2kMsg &N2kMsg); //127258
  void HandleBoatSpeed(const tN2kMsg &N2kMsg);  //128259
  void CalculateTruewind(double Heading, double SOG, double COG, double AWS, double AWA, double &TWS, double &TWD, double &TWA);
public:
  tN2kHandler(tNMEA2000 *_pNMEA2000) : tNMEA2000::tMsgHandler(0,_pNMEA2000) {
  }
  void HandleMsg(const tN2kMsg &N2kMsg);
};
