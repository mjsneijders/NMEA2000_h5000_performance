#include "webconfig.h"
#include "N2kMessages.h"   // use the rad2deg ktstoms etc functions
String WebPageName = "N2K Performance Computer";
//Check if header is present and correct
bool is_authentified() {
   if (webserver.hasHeader("Cookie")) {
    String cookie = webserver.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return true;
    }
  }
  return false;
}

//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (webserver.hasHeader("Cookie")) {
    String cookie = webserver.header("Cookie");
  }
  if (webserver.hasArg("DISCONNECT")) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    webserver.send(301);
    return;
  }
  if (webserver.hasArg("PASSWORD")) {
    if (webserver.arg("PASSWORD") == Configdata.Device.Password.get()) {
      webserver.sendHeader("Location", "/");
      webserver.sendHeader("Cache-Control", "no-cache");
      webserver.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      webserver.send(301);
      return;
    }
    msg = "Wrong username/password! try again.";
  }
  String content = getHead(WebPageName);
  content += "<form action='/login' method='POST'>";
  content += "Password:<input type='password' name='PASSWORD' placeholder='password'>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
  content += getFoot();  
  webserver.send(200, "text/html", content);
}
void handleLogout() {
  webserver.sendHeader("Location", "/");
  webserver.sendHeader("Cache-Control", "no-cache");
  webserver.sendHeader("Set-Cookie", "ESPSESSIONID=0");
  webserver.send(301);
  return;
}


/* //root page can be accessed only if authentification is ok
void handleRoot() {
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authentified()) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
    return;
  }
  String content = "<html><body><H2>hello, you successfully connected to esp32!</H2><br>";
  if (webserver.hasHeader("User-Agent")) {
    content += "the user agent used is : " + webserver.header("User-Agent") + "<br><br>";
  }
  content += "You can access this page until you <a href=\"/login?DISCONNECT=YES\">disconnect</a></body></html>";
  webserver.send(200, "text/html", content);
}
//*/
//no need authentification
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webserver.uri();
  message += "\nMethod: ";
  message += (webserver.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webserver.args();
  message += "\n";
  for (uint8_t i = 0; i < webserver.args(); i++) {
    message += " " + webserver.argName(i) + ": " + webserver.arg(i) + "\n";
  }
  webserver.send(404, "text/plain", message);
}

//setup the webserver to use the various pages
void setupWebserver(){
      webserver.on("/", startPage);
      webserver.on("/login", handleLogin);
      webserver.on("/logout", handleLogout);
      webserver.on("/wifi", wifiPage); 
      webserver.on("/sources", sourcesPage); 
      webserver.on("/n2k", n2kPage); 
      webserver.on("/calculations", calculationsPage); 
      webserver.on("/adjustments", adjustmentsPage); 
      
      webserver.on("/inline", []() {
            webserver.send(200, "text/plain", "this works without need of authentification");
      });
    
      webserver.onNotFound(handleNotFound);
      //here the list of headers to be recorded
      const char * headerkeys[] = {"User-Agent", "Cookie"} ;
      size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
      //ask webserver to track these headers
      webserver.collectHeaders(headerkeys, headerkeyssize);
      webserver.begin();
      Serial.println("HTTP webserver started");
      delay(1000); 


}

void startPage() {

  String content = getHead(WebPageName);
  content += "<B>";
  if (is_authentified()) {
      content += "<a href=\"/wifi\">WiFi settings</a>";
  }else{
      content += "WiFi settings";
  }
  content += "</B>";
  content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Mode:") + 
          pageAddValue(Configdata.Wifi.Mode.get() == 0 ? "Access Point" :  "Client")
        )+    
        pageAddRow(
          pageAddValue ("ssid:") + 
          pageAddValue ((String)Configdata.Wifi.ssid.get() )
        )+
        pageAddRow(
          pageAddValue ("password:") + 
          pageAddValue ((String)Configdata.Wifi.password.get() )
        )+
        pageAddRow(
          pageAddValue ("IP Address: ")+
          pageAddValue ( Configdata.Wifi.Mode.get() == 0 ?  (get8bit(Configdata.Wifi.ip1.get()) +"."+get8bit(Configdata.Wifi.ip2.get()) +"."+get8bit(Configdata.Wifi.ip3.get()) +"." +get8bit(Configdata.Wifi.ip4.get()))  : WiFi.localIP().toString() )
        )    
    );
 
  content += "<BR><B>";
   if (is_authentified()) {
      content += "<a href=\"/sources\">Sources</a>";
  }else{
      content += "Sources"; 
  }
  content += "</B>";
  content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Gps:") + 
          pageAddValue(get8bit(Configdata.Sources.Gps.get()))
        )+    
        pageAddRow(
          pageAddValue ("Speed Trough Water: ") + 
          pageAddValue (get8bit(Configdata.Sources.Water.get()) )
        )+
        pageAddRow(
          pageAddValue ("Compass:") + 
          pageAddValue (get8bit(Configdata.Sources.Compass.get()) )
        )+
        pageAddRow(
          pageAddValue ("Wind: ")+
          pageAddValue (get8bit(Configdata.Sources.Wind.get()) )
        )+    
        pageAddRow(
          pageAddValue ("Variation: ")+
          pageAddValue (get8bit(Configdata.Sources.Variation.get()) )
        )     
    );


  content += "<BR><B>";
  if (is_authentified()) {
      content += "<a href=\"/n2k\">NMEA2000 device</a>";
  }else{
      content += "NMEA2000 device";
  }
  content += "</B>";
  content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Name:") + 
          pageAddValue((String)Configdata.Nmea2000.Name.get())
        )+    
        pageAddRow(
          pageAddValue ("Address: ") + 
          pageAddValue (get8bit(Configdata.Nmea2000.Address.get()) )
        )
    );
  
  content += "<BR><B>";
   if (is_authentified()) {
      content += "<a href=\"/calculations\">Calculations</a>";
  }else{
      content += "Calculations";
  }
  content += "</B>";
    content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Calculate Variation:") + 
          pageAddValue(get8bit(Configdata.Calculation.CalculateVariation.get()))
        )+
       pageAddRow(
          pageAddValue ("Send Variation:") + 
          pageAddValue(get8bit(Configdata.Calculation.SendVariation.get()))
        )+ 
       pageAddRow(
          pageAddValue ("Calculate TrueWind:") + 
          pageAddValue(get8bit(Configdata.Calculation.CalculateTrueWind.get()))
        )+ 
       pageAddRow(
          pageAddValue ("Send TrueWind:") + 
          pageAddValue(get8bit(Configdata.Calculation.SendTrueWind.get()))
        )+ 
       pageAddRow(
          pageAddValue ("Calculate Tide:") + 
          pageAddValue(get8bit(Configdata.Calculation.CalculateTide.get()))
        )+ 
       pageAddRow(
          pageAddValue ("Send Tide:") + 
          pageAddValue(get8bit(Configdata.Calculation.SendTide.get()))
        )
    );
  content += "<BR><B>";
   if (is_authentified()) {
      content += "<a href=\"/adjustments\">Adjustments</a>";
  }else{
      content += "Adjustments";
  }
  content += "</B>";
      content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Speed Through Water: ") + 
          pageAddValue(getdouble(msToKnots(Configdata.Adjustments.WaterSpeed.get())))
        )+
        pageAddRow(
          pageAddValue ("LeeWay: ") + 
          pageAddValue(getdouble(RadToDeg(Configdata.Adjustments.LeeWay.get())))
        )       
    );
  content += "<BR>";

  
  
  if (!is_authentified()) {
    content +="<a href=/login>Login</a> to change settings  ";
  }else{
    content +="<a href=/logout>Logout</a> to logout"; 
  }
  
  
  content += getFoot();
  webserver.send(200, "text/html", content); 
  
  
  }
void wifiPage() {
  String header;
  if (!is_authentified()) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
    return;
  }
  String content = getHead(WebPageName);
  String MODEtxt, ssid, password,SSIDerror, PASSWORDerror, IP1txt, IP2txt, IP3txt, IP4txt, IPerror; 
  uint8_t MODE; 
  uint16_t IP1, IP2, IP3, IP4;
  if (webserver.hasArg("SUBMIT")) {
    
      MODEtxt=webserver.arg("MODE"); 
      Serial.print ((String)"Mode subbmitted was >" + MODEtxt + "<\n"); 
      ssid=webserver.arg("SSID");
      password=webserver.arg("PASSWORD");
      IP1txt=webserver.arg("IP1");
      IP2txt=webserver.arg("IP2");
      IP3txt=webserver.arg("IP3");
      IP4txt=webserver.arg("IP4");
      
      SSIDerror="<font color='red'>less than 20 characters</font>";
      PASSWORDerror="<font color='red'>less than 20 characters</font>";
      IPerror="<font color='red'>must be a valid IP address</font>";
      int error=0; 
      MODE=MODEtxt.toInt();
      if (ssid.length() < 20){
        SSIDerror="";
        error++;
      }
      if (password.length() < 20 ){
        PASSWORDerror="";
        error++;
      }
      if ((IP1=IP1txt.toInt()) &&( IP2=IP2txt.toInt()) && (IP3=IP3txt.toInt()) && (IP4=IP4txt.toInt())  ){
         if ( (IP1 < 256) && (IP2 < 256) && (IP3 < 256) && (IP4 < 256) ){
              IPerror="";
              error++;
         }
      }
      if ( error >2 ){
                Configdata.Wifi.ssid.set(ssid);
                Configdata.Wifi.password.set(password);
                Configdata.Wifi.Mode.set(MODE);
                Configdata.Wifi.ip1.set((uint8_t)IP1);
                Configdata.Wifi.ip2.set((uint8_t)IP2);
                Configdata.Wifi.ip3.set((uint8_t)IP3);
                Configdata.Wifi.ip4.set((uint8_t)IP4);
                Configdata.Wifi.write();
                webserver.sendHeader("Location", "/");
                webserver.sendHeader("Cache-Control", "no-cache");
                webserver.send(301);
                return; 
      }
      
  }else{
      ssid=Configdata.Wifi.ssid.get();
      password=Configdata.Wifi.password.get();
      IP1txt=get8bit(Configdata.Wifi.ip1.get());
      IP2txt=get8bit(Configdata.Wifi.ip2.get());
      IP3txt=get8bit(Configdata.Wifi.ip3.get());
      IP4txt=get8bit(Configdata.Wifi.ip4.get());
      MODE=Configdata.Wifi.Mode.get();
  }  
  
  
  
  content += "wifi page placeholder"; 
  content += "<form action='/wifi' method='POST'>";
      content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Mode") + 
          pageAddValue((String) "<input type=\"radio\" name=\"MODE\" value=\"1\"" + (MODE==1?"checked":"") + " >Client") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"MODE\" value=\"0\" " + (MODE==0?"checked":"") + ">Access Point") +
          pageAddValue( "" ) 
        )+
        pageAddRow(
          pageAddValue ("SSID") + 
          pageAddValue("<input type='text' name='SSID' value='"+ssid+"'>")+
          pageAddValue( SSIDerror) 
        )+
        pageAddRow(
          pageAddValue ("Password") + 
          pageAddValue("<input type='text' name='PASSWORD' value='"+password+"'>")+
          pageAddValue( PASSWORDerror) 
        )+
        pageAddRow(
          pageAddValue ("IP Address") + 
          pageAddValue("<input type='text' name='IP1' size='3' value='"+IP1txt+"'>"+
                       "<input type='text' name='IP2' size='3' value='"+IP2txt+"'>"+
                       "<input type='text' name='IP3' size='3' value='"+IP3txt+"'>"+
                       "<input type='text' name='IP4' size='3' value='"+IP4txt+"'>")+
          pageAddValue( IPerror) 
        )+
       pageAddRow(
          pageAddValue("<input type='submit' name='SUBMIT' value='SUBMIT'>")+
          pageAddValue( "<input type='button' name='cancel' value='cancel' onClick=\"window.location='/';\">")+
          pageAddValue ("") 
        )
    );
  content += "<BR><BR>**  In client mode,  the ip address is irrelevant, the IP address is provided by the AP that is logged into. ";
  content += "<BR>**  Remember to reboot,  changes become active after a reboot.";


  content += "</form>";




// WiFi scannen duurt te lang.   
/*
    content +="<BR><BR><HR><BR>"; 
    int n = WiFi.scanNetworks();
    if (n == 0) {
        content +="no  WiFi networks found";
    } else {
        content += (String)n + " WiFi networks found";
        content += "<table>"; 
        for (int i = 0; i < n; ++i) {
            content+=pageAddRow(
                pageAddValue(WiFi.SSID(i))+
                pageAddValue((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"open":"protected")
                );
        }
        content += "</table>";  
    }
  //*/
  content += getFoot();; 
  webserver.send(200, "text/html", content);
}
void sourcesPage() {
   String header;
  if (!is_authentified()) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
    return;
  }
  uint16_t GPS, WATER, COMPASS, WIND, VARIATION;
  String GPStxt, WATERtxt, COMPASStxt, WINDtxt, VARIATIONtxt;  
  String GPSerror = "" ; 
  String WATERerror = "" ; 
  String WINDerror = "" ; 
  String COMPASSerror = "" ; 
  String VARIATIONerror = "" ; 
  if (webserver.hasArg("SUBMIT")) {
      GPStxt=webserver.arg("GPS");
      WATERtxt=webserver.arg("WATER");
      COMPASStxt=webserver.arg("COMPASS");
      WINDtxt=webserver.arg("WIND");
      VARIATIONtxt=webserver.arg("VARIATION"); 
      GPSerror="<font color='red'>a number between 0 and 255</font>";
      WATERerror="<font color='red'>a number between 0 and 255</font>";
      COMPASSerror="<font color='red'>a number between 0 and 255</font>";
      WINDerror="<font color='red'>a number between 0 and 255</font>";
      VARIATIONerror="<font color='red'>a number between 0 and 255</font>";
      int error=0; 
      if (GPS=GPStxt.toInt()   ){
          if  (GPS < 256 ) {
              GPSerror="";
          }
      }else if ( GPStxt == "0"){
         GPS = 0; 
         GPSerror=""; 
      }else {
        error++; 
      }
      if (WATER=WATERtxt.toInt()){
        if (WATER < 256) {
              WATERerror="";
        }
      }else if ( WATERtxt == "0"){
         WATER = 0; 
         WATERerror=""; 
      }else {
        error++; 
      }
      if (COMPASS=COMPASStxt.toInt()|| GPStxt == "0"){
        if (COMPASS < 256) {
            COMPASSerror="";  
        }
      }else if ( COMPASStxt == "0"){
         COMPASS = 0; 
         COMPASSerror=""; 
      }else {
        error++; 
      }
      if (WIND=WINDtxt.toInt()) {
        //Serial.println ((String) "Wind is " + WIND) ; 
        if (WIND < 256) {
            WINDerror="";   
        }
      }else if ( WINDtxt == "0"){
         WIND = 0; 
         WINDerror=""; 
      }else {
        error++; 
      }
      if (VARIATION=VARIATIONtxt.toInt()) {
       //Serial.println ((String) "VARIATION is " + VARIATION) ; 
        if (VARIATION < 256) {
            VARIATIONerror="";   
        }
      }else if (VARIATIONtxt == "0"){
         VARIATION = 0; 
         VARIATIONerror=""; 
      }else {
        error++; 
      }
       if ( error == 0) {
                Configdata.Sources.Gps.set((uint8_t)GPS); 
                Configdata.Sources.Water.set((uint8_t)WATER); 
                Configdata.Sources.Compass.set((uint8_t)COMPASS); 
                Configdata.Sources.Wind.set((uint8_t)WIND); 
                Configdata.Sources.Variation.set((uint8_t)VARIATION); 
                Configdata.Sources.write();
                webserver.sendHeader("Location", "/");
                webserver.sendHeader("Cache-Control", "no-cache");
                webserver.send(301);
                return; 
       }
      
  }else{
      GPStxt=get8bit(Configdata.Sources.Gps.get());
      WATERtxt=get8bit(Configdata.Sources.Water.get());
      COMPASStxt=get8bit(Configdata.Sources.Compass.get());
      WINDtxt=get8bit(Configdata.Sources.Wind.get());
      VARIATIONtxt=get8bit(Configdata.Sources.Variation.get());
  }
  String content = getHead(WebPageName);
  content += "<form action='/sources' method='POST'>";
      content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("GPS") + 
          pageAddValue("<input type='text' name='GPS' value='"+GPStxt+"'>")+
          pageAddValue( GPSerror) 
        )+
        pageAddRow(
          pageAddValue ("WATER") + 
          pageAddValue("<input type='text' name='WATER' value='"+WATERtxt+"'>")+
          pageAddValue( WATERerror) 
        )+
        pageAddRow(
          pageAddValue ("Compass") + 
          pageAddValue("<input type='text' name='COMPASS' value='"+COMPASStxt+"'>")+
          pageAddValue( COMPASSerror) 
        )+
        pageAddRow(
          pageAddValue ("Wind") + 
          pageAddValue("<input type='text' name='WIND' value='"+WINDtxt+"'>")+
          pageAddValue( WINDerror) 
        )+
       pageAddRow(
          pageAddValue ("Variation") + 
          pageAddValue("<input type='text' name='VARIATION' value='"+VARIATIONtxt+"'>")+
          pageAddValue( WINDerror) 
        )+
       pageAddRow(
          pageAddValue("<input type='submit' name='SUBMIT' value='SUBMIT'>")+
          pageAddValue( "<input type='button' name='cancel' value='cancel' onClick=\"window.location='/';\">")+
          pageAddValue ("") 
        )
    );
  content += "";


  content += "</form>";
  content += "<BR><BR> ** if a value of 255 is entered,  the source id for the values is ignored. ";
  content += getFoot();
  webserver.send(200, "text/html", content);
}
void n2kPage() {
  String header;
  if (!is_authentified()) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
    return;
  }
  uint16_t ADDRESS;
  String NAME, ADDRESStxt;  
  String NAMEerror = "" ; 
  String ADDRESSerror = "" ;
  if (webserver.hasArg("SUBMIT")) {
      NAME=webserver.arg("NAME");
      ADDRESStxt=webserver.arg("ADDRESS"); 
      Serial.print ("data was submitted from n2kpage:  "+ NAME +"\n"); 
      ADDRESSerror="<font color='red'>a number below 250</font>";
      NAMEerror="<font color='red'>must have 1 to 18 chars</font>";
      int error=0; 
      if (ADDRESS=ADDRESStxt.toInt() ){
          if  (ADDRESS < 250 ) {
              ADDRESSerror="";
              error++;
          }
      }
      if (NAME.length() > 0 && NAME.length()< 19  ){
         error++; 
         NAMEerror=""; 
      }
      if ( error > 1){
                Configdata.Nmea2000.Name.set(NAME);
                Configdata.Nmea2000.Address.set(ADDRESS);
                Configdata.Nmea2000.write();
                webserver.sendHeader("Location", "/");
                webserver.sendHeader("Cache-Control", "no-cache");
                webserver.send(301);
                return; 
      }
  }else{
      NAME=Configdata.Nmea2000.Name.get();
      ADDRESStxt=get8bit(Configdata.Nmea2000.Address.get());
  }
  String content = getHead(WebPageName);
  content += "<form action='/n2k' method='POST'>";
      content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Name") + 
          pageAddValue("<input type='text' name='NAME' value='"+NAME+"'>")+
          pageAddValue( NAMEerror) 
        )+
        pageAddRow(
          pageAddValue ("Address") + 
          pageAddValue("<input type='text' name='ADDRESS' value='"+ADDRESStxt+"'>")+
          pageAddValue( ADDRESSerror) 
        )+
       pageAddRow(
          pageAddValue("<input type='submit' name='SUBMIT' value='SUBMIT'>")+
          pageAddValue( "<input type='button' name='cancel' value='cancel' onClick=\"window.location='/';\">")+
          pageAddValue ("") 
        )
    );
  


  content += "</form>";
  
  content += getFoot();
  webserver.send(200, "text/html", content);


}
void calculationsPage() {
  String header;
  if (!is_authentified()) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
    return;
  }
  uint16_t CALVAR, SENDVAR, CALTW, SENDTW, CALTIDE, SENDTIDE;
  String CALVARtxt, SENDVARtxt, CALTWtxt, SENDTWtxt, CALTIDEtxt, SENDTIDEtxt; 
  int error = 0; 
  if (webserver.hasArg("SUBMIT")) {
        CALVARtxt=webserver.arg("CALVAR");
        Serial.println("CALVAR value submitted: " + CALVARtxt); 
       if ( CALVARtxt == "0" ) {
          CALVAR=0; 
       }else if ( CALVARtxt == "1" ) {
          CALVAR=1; 
       }else{
          Serial.println("CALVAR value submitted ("+CALVARtxt + ") was weird");
          error=1; 
       }
        SENDVARtxt=webserver.arg("SENDVAR");
        Serial.println("SENDVAR value submitted: " + SENDVARtxt); 
       if ( SENDVARtxt == "0" ) {
          SENDVAR=0; 
       }else if ( SENDVARtxt == "1" ) {
          SENDVAR=1; 
       }else{
          Serial.println("SENDVAR value submitted ("+SENDVARtxt + ") was weird");
          error=1; 
       }
        CALTWtxt=webserver.arg("CALTW");
        Serial.println("CALTW value submitted: " + CALTWtxt); 
       if ( CALTWtxt == "0" ) {
          CALTW=0; 
       }else if ( CALTWtxt == "1" ) {
          CALTW=1; 
       }else{
          Serial.println("CALTW value submitted ("+CALTWtxt + ") was weird");
          error=1; 
       }
        SENDTWtxt=webserver.arg("SENDTW");
        Serial.println("SENDTW value submitted: " + SENDTWtxt); 
       if ( SENDTWtxt == "0" ) {
          SENDTW=0; 
       }else if ( SENDTWtxt == "1" ) {
          SENDTW=1; 
       }else{
          Serial.println("SENDTW value submitted ("+SENDTWtxt + ") was weird");
          error=1; 
       }
        CALTIDEtxt=webserver.arg("CALTIDE");
        Serial.println("CALTIDE value submitted: " + CALTIDEtxt); 
       if ( CALTIDEtxt == "0" ) {
          CALTIDE=0; 
       }else if ( CALTIDEtxt == "1" ) {
          CALTIDE=1; 
       }else{
          Serial.println("CALTIDE value submitted ("+CALTIDEtxt + ") was weird");
          error=1; 
       }
        SENDTIDEtxt=webserver.arg("SENDTIDE");
        Serial.println("SENDTIDE value submitted: " + SENDTIDEtxt); 
       if ( SENDTIDEtxt == "0" ) {
          SENDTIDE=0; 
       }else if ( SENDTIDEtxt == "1" ) {
          SENDTIDE=1; 
       }else{
          Serial.println("SENDTIDE value submitted ("+SENDTIDEtxt + ") was weird");
          error=1; 
       }        
        if (error == 0){
            Configdata.Calculation.CalculateVariation.set(CALVAR);
            Configdata.Calculation.SendVariation.set(SENDVAR);
            Configdata.Calculation.CalculateTrueWind.set(CALTW);
            Configdata.Calculation.SendTrueWind.set(SENDTW);
            Configdata.Calculation.CalculateTide.set(CALTIDE);
            Configdata.Calculation.SendTide.set(SENDTIDE); 
            Configdata.Calculation.write();
            webserver.sendHeader("Location", "/");
            webserver.sendHeader("Cache-Control", "no-cache");
            webserver.send(301);
            return; 
        }
  }else{
        CALVAR=Configdata.Calculation.CalculateVariation.get();
        SENDVAR=Configdata.Calculation.SendVariation.get();
        CALTW=Configdata.Calculation.CalculateTrueWind.get();
        SENDTW=Configdata.Calculation.SendTrueWind.get();
        CALTIDE=Configdata.Calculation.CalculateTide.get();
        SENDTIDE=Configdata.Calculation.SendTide.get();
  }
  String content = getHead(WebPageName);
  content += "<form action='/calculations' method='POST'>";
      content += pageAddTable ( 
          pageAddRow(
          pageAddValue ("Calculate Variation ( WMM2020) ") + 
          pageAddValue((String) "<input type=\"radio\" name=\"CALVAR\" value=\"1\"" + (CALVAR==1?"checked":"") + " >Yes") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"CALVAR\" value=\"0\" " + (CALVAR==0?"checked":"") + ">No") +
          pageAddValue( "" ) 
        )+
          pageAddRow(
          pageAddValue ("Send Variation to NMEA2000 ") + 
          pageAddValue((String) "<input type=\"radio\" name=\"SENDVAR\" value=\"1\"" + (SENDVAR==1?"checked":"") + " >Yes") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"SENDVAR\" value=\"0\" " + (SENDVAR==0?"checked":"") + ">No") +
          pageAddValue( "" ) 
        )+
          pageAddRow(
          pageAddValue ("Calculate TrueWind ") + 
          pageAddValue((String) "<input type=\"radio\" name=\"CALTW\" value=\"1\"" + (CALTW==1?"checked":"") + " >Yes") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"CALTW\" value=\"0\" " + (CALTW==0?"checked":"") + ">No") +
          pageAddValue( "" ) 
        )+
          pageAddRow(
          pageAddValue ("Send TrueWind to NMEA2000 ") + 
          pageAddValue((String) "<input type=\"radio\" name=\"SENDTW\" value=\"1\"" + (SENDTW==1?"checked":"") + " >Yes") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"SENDTW\" value=\"0\" " + (SENDTW==0?"checked":"") + ">No") +
          pageAddValue( "" ) 
        )+
          pageAddRow(
          pageAddValue ("Calculate Tide") + 
          pageAddValue((String) "<input type=\"radio\" name=\"CALTIDE\" value=\"1\"" + (CALTIDE==1?"checked":"") + " >Yes") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"CALTIDE\" value=\"0\" " + (CALTIDE==0?"checked":"") + ">No") +
          pageAddValue( "" ) 
        )+
          pageAddRow(
          pageAddValue ("Send Tide to NMEA2000 ") + 
          pageAddValue((String) "<input type=\"radio\" name=\"SENDTIDE\" value=\"1\"" + (SENDTIDE==1?"checked":"") + " >Yes") +
          pageAddValue("") 
        )+
        pageAddRow(
          pageAddValue ("") + 
          pageAddValue((String) "<input type=\"radio\" name=\"SENDTIDE\" value=\"0\" " + (SENDTIDE==0?"checked":"") + ">No") +
          pageAddValue( "" ) 
        )+

        
        pageAddRow(
          pageAddValue("<input type='submit' name='SUBMIT' value='SUBMIT'>")+
          pageAddValue( "<input type='button' name='cancel' value='cancel' onClick=\"window.location='/';\">")+
          pageAddValue ("") 
        )
    );



  content += "</form>";
  
  content += getFoot();
  webserver.send(200, "text/html", content);

}
void adjustmentsPage() {
  String header;
  if (!is_authentified()) {
    webserver.sendHeader("Location", "/login");
    webserver.sendHeader("Cache-Control", "no-cache");
    webserver.send(301);
    return;
  }
  double ADJSTW, ADJLEEWAY;
  String ADJSTWtxt, ADJLEEWAYtxt, ADJSTWerror, ADJLEEWAYerror;

  
  uint8_t error = 0; 
  if (webserver.hasArg("SUBMIT")) {
       
      
      ADJSTWtxt=webserver.arg("ADJSTW");
      Serial.print ("STW adjustment from webpage:  "+ ADJSTWtxt +"\n"); 
      if (ADJSTW=ADJSTWtxt.toDouble()){
                ADJSTWerror=""; 
      }else if (ADJSTWtxt == "0" ||ADJSTWtxt == "0.0000"){
                ADJSTW=0.0; 
                ADJSTWerror=""; 
      }else{
              ADJSTWerror= "<font color='red'>use a float value</font>"; 
              error++; 
      }
      ADJLEEWAYtxt=webserver.arg("ADJLEEWAY");
      Serial.print ("STW adjustment from webpage:  "+ ADJSTWtxt +"\n"); 
      if (ADJLEEWAY=ADJLEEWAYtxt.toDouble()){
                ADJLEEWAYerror=""; 
      }else if (ADJLEEWAYtxt == "0" | ADJLEEWAYtxt == "0.0000"){
                ADJLEEWAY=0.0; 
                ADJLEEWAYerror=""; 
      }else{
              ADJLEEWAYerror= "<font color='red'>use a float value</font>"; 
              error++; 
      }
      if ( error == 0 ){ 
                Configdata.Adjustments.WaterSpeed.set(KnotsToms(ADJSTW)); 
                Configdata.Adjustments.LeeWay.set(DegToRad(ADJLEEWAY)); 
                Configdata.Adjustments.write();
                webserver.sendHeader("Location", "/");
                webserver.sendHeader("Cache-Control", "no-cache");
                webserver.send(301);
                return; 
      }
  }else{
      ADJSTWtxt=getdouble(msToKnots(Configdata.Adjustments.WaterSpeed.get())); 
      ADJLEEWAYtxt=getdouble(RadToDeg(Configdata.Adjustments.LeeWay.get())); 
  }
  String content = getHead(WebPageName);
  content += "<form action='/adjustments' method='POST'>";
      content += pageAddTable ( 
        pageAddRow(
          pageAddValue ("Adjust STW (+/-Kts)") + 
          pageAddValue("<input type='text' name='ADJSTW' value='"+ADJSTWtxt+"'>") +
          pageAddValue(ADJSTWerror)
        )+
       pageAddRow(
          pageAddValue ("Adjust Leeway (+/-Deg)") + 
          pageAddValue("<input type='text' name='ADJLEEWAY' value='"+ADJLEEWAYtxt+"'>") +
          pageAddValue(ADJLEEWAYerror)
        )+
       pageAddRow(
          pageAddValue("<input type='submit' name='SUBMIT' value='SUBMIT'>")+
          pageAddValue( "<input type='button' name='cancel' value='cancel' onClick=\"window.location='/';\">")+
          pageAddValue ("") 
        )
    );
  


  content += "</form>";
  
  content += getFoot();
  webserver.send(200, "text/html", content);

}





String getStyle(){
    String style = "<style> table { empty-cells: show; }H1 { color: maroon; margin-left: 40px; } .content { max-width: 500px; margin: auto; } .header { background-color: linen; } </style>";
    return style; 
}
String getHead(String content){ 
  String header =  "<html><head>" + getStyle() + "</head><body><div class=\"header\"> <HR> <H1> <center>"+ content +" </center> </H1> <HR> </div><div class=\"content\"> <center> ";
    return header;
 
}
String getFoot(String content){ 
  String header = "</center> </div><div class=\"footer\">"+ content +"</div></body> </html>";
    return header;

}
String pageAddTable(String content){ 
  String header = "<table>"+ content +"</table>";
    return header;

}
String pageAddRow(String content){ 
  String header = "<tr>"+ content +"</tr>";
    return header;

}
String pageAddValue(String content){ 
  String header = "<td>"+ content +"</td>";
    return header;

}
String get8bit(uint8_t Number){
  char Buf[4]; 
  itoa(Number,Buf,10); 
  return (String)Buf; 
}
String get16bit(uint16_t Number){
  char Buf[6]; 
  itoa(Number,Buf,10); 
  return (String)Buf; 
}
String get32bit(uint32_t Number){
  char Buf[11]; 
  itoa(Number,Buf,10); 
  return (String)Buf; 
}
String getdouble(double Number){
  return String(Number, 4);
}
