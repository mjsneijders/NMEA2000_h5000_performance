#include "NMEA2000_h5000.h"
#include "N2kMessages.h"

void SetN2kPGN130824(tN2kMsg& N2kMsg, sPerformanceData &PerformanceData) {
    N2kMsg.SetPGN(130824L);
    N2kMsg.Priority=3;
   // N2kMsg.AddByte(SID);
	AddPerformanceValue (N2kMsg,0x7f,0x20,Performancedata.VMG,1e-02);                	//Velocity Made Good  (m/s)
	AddPerformanceValue (N2kMsg,0x38,0x21,Performancedata.GroundWind,1e-02);	 		//Ground Wind Speed (m/s)
	AddPerformanceValue (N2kMsg,0x36,0x21,Performancedata.NextLegTgtSpeed,1e-02);    	// Next Leg Target Speed (m/s)
	AddPerformanceValue (N2kMsg,0x1d,0x21,Performancedata.VMGperf,1e-03);		 		// VMG performance ( percent) 
	AddPerformanceValue (N2kMsg,0x7e,0x20,Performancedata.PolarBoatSpeed,1e-02); 		// Polar Boatspeed (m/s)
	AddPerformanceValue (N2kMsg,0x7c,0x20,Performancedata.PolarPerf,1e-03);		 		// Polar Performance (percent)
	AddPerformanceValue (N2kMsg,0x53,0x20,Performancedata.TgtTWA,1e-04);	     		// Target TWA (rad)
	AddPerformanceValue (N2kMsg,0x83,0x20,Performancedata.TideRate,1e-02);		 		// Tide Rate (m/s)
	AddPerformanceValue (N2kMsg,0x84,0x20,Performancedata.TideSet,1e-04);		 		// Tide Set (rad)
	AddPerformanceValue (N2kMsg,0x31,0x21,Performancedata.OppTackCOG,1e-04);	 		// Opposite Tack COG (rad)
	AddPerformanceValue (N2kMsg,0x35,0x21,Performancedata.NextLegBearing,1e-04); 		// Next Leg Bearing (rad)
	AddPerformanceValue (N2kMsg,0x37,0x21,Performancedata.GroundWindDirection,1e-04); 	// Ground Wind Direction (rad)
	AddPerformanceValue (N2kMsg,0x33,0x21,Performancedata.OppTackTgtHeading,1e-04);  	// Opposite Tack Target Heading (rad)
	AddPerformanceValue (N2kMsg,0x50,0x21,Performancedata.AverageTrueWindDirection,1e-04);	// Average True Wind Direction (rad)
	AddPerformanceValue (N2kMsg,0x69,0x21,Performancedata.Course,1e-04);		  		//Course over ground (rad)
	AddPerformanceValue (N2kMsg,0xd3,0x20,Performancedata.DrBearing,1e-04);		  		// Dead Reckoning Bearing(rad)
	AddPerformanceValue (N2kMsg,0x81,0x20,Performancedata.DrDistance,1e-02);	  		// Dead Reckoning Distance (m)
	AddPerformanceValue (N2kMsg,0x31,0x21,Performancedata.BiasAdvantage,1e-02);	  		// Bias Advantage (m)
	AddPerformanceValue (N2kMsg,0x9a,0x20,Performancedata.oppTackCOG,1e-04);	  		// Heading on Opposite Tack (true) (rad)
	AddPerformanceValue (N2kMsg,0x32,0x20,Performancedata.TackingPerf,1e-03);      		// Tacking Performance (percent)
	AddPerformanceValue (N2kMsg,0x82,0x20,Performancedata.LeewayAngle,1e-04);      		// Leeway Angle (rad)
	AddPerformanceValue (N2kMsg,0x82,0x20,Performancedata.HeelAngle,1e-04);		  		// Heel Angle (rad)
	AddPerformanceValue (N2kMsg,0x9b,0x20,Performancedata.TrimAngle,1e-04);          	// Trim Angle (rad)
	AddPerformanceValue (N2kMsg,0x35,0x20,Performancedata.OptimalWindAngle,1e-04);   	// Optimal Wind Angle (rad)
	AddPerformanceValue (N2kMsg,0x34,0x21,Performancedata.MastRake,1e-04);         		// Mast Rake(rad)
	AddPerformanceValue (N2kMsg,0x9d,0x20,Performancedata.WindAngleMast,1e-04);      	// Wind Angle To Mast(rad)
	AddPerformanceValue (N2kMsg,0x51,0x21,Performancedata.WindPhase, 1e-04);     		// Wind Phase (rad)
	AddPerformanceValue (N2kMsg,0x52,0x21,Performancedata.WindLift, 1e-04);		 		// Wind Lift (rad)
	AddPerformanceValue (N2kMsg,0x1c,0x21,Performancedata.ChainLength, 1e-02);	 		// Chain Length (m)
}

void AddPerformanceValue ( tN2kMsg& N2kMsg, byte FirstByte, byte SecondByte, double Value, double precision){
		if (!N2kIsNA(Value)){
			N2kMsg.AddByte(FirstByte);
			N2kMsg.AddByte(SecondByte); 
			N2kMsg.Add2ByteUDouble( Value,precision);
		}
}