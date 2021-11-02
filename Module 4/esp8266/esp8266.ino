#include <ESP8266WiFi.h>
#include<I2C_Anything.h>
int minutes = 10;

int timeDelay = 1000 * 60 * minutes;    //one loop will continue "timeDelay" time
String apiKey_14  = "8ZMC3PI8837NSTD3";
const char *ssid = "RoboDoc";
const char *pass = "RoboDoc#";
const char* server = "api.thingspeak.com";
WiFiClient client;

float temp_4_up, temp_4_middle, temp_4_down;


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Connecting to ");
   Serial.println(ssid); 
   WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) 
       {
              delay(500);
              Serial.print(".");
       }
  Serial.println("");
  Serial.println("WiFi connected");
    while (!Serial) {;}
}

void loop()
{  
  Wire.requestFrom(0x04, 24);
  I2C_readAnything(temp_4_up);
  I2C_readAnything(temp_4_middle);
  I2C_readAnything(temp_4_down);
  Serial.print("Board 4: ");
  Serial.print(temp_4_up , 2); Serial.print(" | ");
  Serial.print(temp_4_middle , 2); Serial.print(" | ");
  Serial.println(temp_4_down , 2);
  Serial.println("------------------------------------------------------------");

  delay(1000);

  if (client.connect(server,80))   //   
          {          
           String postStr = apiKey_14;
               postStr +="&field1=";
               postStr += String(temp_4_up);
               postStr +="&field2=";
               postStr += String(temp_4_middle);
               postStr +="&field3=";
               postStr += String(temp_4_down);
               postStr += "\r\n\r\n\r\n";
            
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKapiKey_4: "+apiKey_14+"\n");
           client.print("Content-Type: application/x-www-form-urlencoded\n");
           client.print("Content-Length: ");
           client.print(postStr.length());
           client.print("\n\n");
           client.print(postStr);        
           Serial.println("Send to Online Cloud.");
          }
           client.stop();

delay(timeDelay);

}
