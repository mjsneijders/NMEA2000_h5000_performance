


void SetN2kPGN130824(tN2kMsg& N2kMsg, unsigned char SID, tN2kRangeResidualMode Mode) {
    N2kMsg.SetPGN(130824L);
    N2kMsg.Priority=3;
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte(0x7f);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( VMG,1e-02)                //Velocity Made Good  (m/s)
	N2kMsg.AddByte(0x38);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( GroundWind,1e-02)		 //Ground Wind Speed (m/s)
	N2kMsg.AddByte(0x36);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( NextLegTgtSpeed,1e-02)    // Next Leg Target Speed (m/s)
	N2kMsg.AddByte(0x1d);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( VMGperf,1e-03)			 // VMG performance ( percent) 
	N2kMsg.AddByte(0x7e);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( PolarBoatSpeed,1e-02)	 // Polar Boatspeed (m/s)
	N2kMsg.AddByte(0x7c);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( PolarPerf,1e-03)			 // Polar Performance (percent)
	N2kMsg.AddByte(0x53);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( TgtTWA,1e-04)		     // Target TWA (rad)
	N2kMsg.AddByte(0x83);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( TideRate,1e-02)			 // Tide Rate (m/s)
	N2kMsg.AddByte(0x84);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( TideSet,1e-04)			 // Tide Set (rad)
	N2kMsg.AddByte(0x31);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( OppTackCOG,1e-04)		 // Opposite Tack COG (rad)
	N2kMsg.AddByte(0x35);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( NextLegBearing,1e-04)	 // Next Leg Bearing (rad)
	N2kMsg.AddByte(0x37);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( GroundWindDirection,1e-04) // Ground Wind Direction (rad)
	N2kMsg.AddByte(0x33);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( OppTackTgtHeading,1e-04)	  // Opposite Tack Target Heading (rad)
	N2kMsg.AddByte(0x50);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( AverageTrueWindDirection,1e-04)	// Average True Wind Direction (rad)
	N2kMsg.AddByte(0x69);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( Course,1e-04)			  //Course over ground (rad)
	N2kMsg.AddByte(0xd3);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( DrBearing,1e-04)			  // Dead Reckoning Bearing(rad)
	N2kMsg.AddByte(0x81);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( DrDistance,1e-02)		  // Dead Reckoning Distance (m)
	N2kMsg.AddByte(0x31);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( BiasAdvantage,1e-02)		  // Bias Advantage (m)
	N2kMsg.AddByte(0x9a);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( oppTackCOG,1e-04)		  // Heading on Opposite Tack (true) (rad)
	N2kMsg.AddByte(0x32);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( TackingPerf,1e-03)	      // Tacking Performance (percent)
	N2kMsg.AddByte(0x82);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( LeewayAngle,1e-04)	      // Leeway Angle (rad)
	N2kMsg.AddByte(0x82);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( HeelAngle,1e-04)			  // Heel Angle (rad)
	N2kMsg.AddByte(0x9b);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( TrimAngle,1e-04)          // Trim Angle (rad)
	N2kMsg.AddByte(0x35);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( OptimalWindAngle,1e-04)   // Optimal Wind Angle (rad)
	N2kMsg.AddByte(0x34);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( MastRake,1e-04)          // Mast Rake(rad)
	N2kMsg.AddByte(0x9d);N2kMsg.AddByte(0x20); N2kMsg.Add2ByteUDouble( WindAngleMast,1e-04)      // Wind Angle To Mast(rad)
	N2kMsg.AddByte(0x51);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( WindPhase, 1e-04)	     // Wind Phase (rad)
	N2kMsg.AddByte(0x52);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( WindLift, 1e-04)			 // Wind Lift (rad)
	N2kMsg.AddByte(0x1c);N2kMsg.AddByte(0x21); N2kMsg.Add2ByteUDouble( ChainLength, 1e-02)		 // Chain Length (m)

}