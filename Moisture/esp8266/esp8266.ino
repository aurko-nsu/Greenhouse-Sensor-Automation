#include <ESP8266WiFi.h>
#include<I2C_Anything.h>
int minutes = 10;

int timeDelay = 1000 * 60 * minutes;
String apiKey_8  = "WYZE2W7LB2K227T0";
const char *ssid = "RoboDoc"; 
const char *pass = "RoboDoc#";
const char* server = "api.thingspeak.com";
WiFiClient client;

float moisture_2_float, moisture_8_float;
int moisture_2, moisture_8;


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
  Wire.requestFrom(0x08, 24);
  I2C_readAnything(moisture_2_float);
  I2C_readAnything(moisture_8_float);
  moisture_2 = moisture_2_float;
  moisture_8 = moisture_8_float;
  Serial.print("Board 8: ");
  Serial.print(moisture_2_float , 2); Serial.print(" | ");
  Serial.println(moisture_8_float , 2);
  Serial.println("------------------------------------------------------------");

  delay(1000);

  if (client.connect(server,80))   
          {          
           String postStr = apiKey_8;
               postStr +="&field1=";
               postStr += String(moisture_2);
               postStr +="&field2=";
               postStr += String(moisture_8);
               postStr += "\r\n\r\n";
            
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKapiKey_4: "+apiKey_8+"\n");
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
