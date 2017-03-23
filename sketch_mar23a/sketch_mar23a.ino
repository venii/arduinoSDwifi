


#include <ESP8266WiFi.h>        
#include <DNSServer.h>            
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <aREST.h>

WiFiManager wifiManager;
aREST rest = aREST();

//definição dos hooks
int pegaValorSensorControl(String command);

WiFiServer server(81);

void setup() {
   Serial.begin(9600);
  //int status = WL_IDLE_STATUS;
  // put your setup code here, to run once:
  //status = WiFi.begin("w3GET","minhavisita");
  //Serial.println("Start WIFI "+status);

  WiFi.begin("w3GET","minhavisita");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //wifiManager.setAPCallback(configModeCallback);
  //wifiManager.autoConnect("w3GET","minhavisita");
  Serial.println("Start  WIFI MANAGER");

  int temperature = 24;
  int humidity = 40;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);
  
  //ASSIGN HOOKS API FUNCOEES
  rest.function("pegaValorSensorControl",pegaValorSensorControl);

  rest.set_id("1");
  rest.set_name("esp8266");
  
  server.begin();
  
  Serial.println("Server started");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("ABRINDO CONFIG WIFI");
  

  WiFiClient client = server.available();
  Serial.println("available "+client);
  rest.handle(client);
  Serial.println("API OK");
  
  wifiManager.startConfigPortal("w3GET");
}
/*FUNÇOES DA API*/
int pegaValorSensorControl(String command) {

  // Get state from command
  int state = command.toInt();
  Serial.println("Parametro API "+state);
  //digitalWrite(6,state);
  return 1;
}
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}



