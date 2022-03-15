#ifndef _H5000_H_
#define _H5000_H_
#include "N2kMessages.h"


struct sPerformanceData{
	double VMG=N2kDoubleNA;             
	double GroundWind=N2kDoubleNA;	
	double NextLegTgtSpeed=N2kDoubleNA; 
	double VMGperf=N2kDoubleNA;			
	double PolarBoatSpeed=N2kDoubleNA;
	double PolarPerf=N2kDoubleNA;			
	double TgtTWA=N2kDoubleNA;	    
	double TideRate=N2kDoubleNA;	
	double TideSet=N2kDoubleNA;		
	double OppTackCOG=N2kDoubleNA;	
	double NextLegBearing=N2kDoubleNA;
	double GroundWindDirection=N2kDoubleNA;
	double OppTackTgtHeading=N2kDoubleNA;
	double AverageTrueWindDirection=N2kDoubleNA;
	double Course=N2kDoubleNA;		
	double DrBearing=N2kDoubleNA;		
	double DrDistance=N2kDoubleNA;	
	double BiasAdvantage=N2kDoubleNA;		
	double oppTackCOG=N2kDoubleNA;	
	double TackingPerf=N2kDoubleNA;    
	double LeewayAngle=N2kDoubleNA;	    
	double HeelAngle=N2kDoubleNA;			
	double TrimAngle=N2kDoubleNA;        
	double OptimalWindAngle=N2kDoubleNA; 
	double MastRake=N2kDoubleNA;         
	double WindAngleMast=N2kDoubleNA;   
	double WindPhase=N2kDoubleNA;    
	double WindLift=N2kDoubleNA;		
	double ChainLength=N2kDoubleNA;	
};


void SetN2kPGN130824(tN2kMsg& N2kMsg, sPerformanceData PerformanceData);
void AddPerformanceValue (tN2kMsg& N2kMsg, byte FirstByte, byte SecondByte, double Value, double precision);

#endif // _H5000_H_