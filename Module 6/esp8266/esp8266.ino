#include <ESP8266WiFi.h>
#include<I2C_Anything.h>
int minutes = 10;
int timeDelay = 1000 * 60 * minutes;

String apiKey_69  = "CBCB78WUPIDR9CZ1";
const char *ssid = "RoboDoc";  
const char *pass = "RoboDoc#";
const char* server = "api.thingspeak.com";
WiFiClient client;

float temp_6_up, temp_6_middle, temp_6_down;

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
  Wire.requestFrom(0x06, 24);
  I2C_readAnything(temp_6_up);
  I2C_readAnything(temp_6_middle);
  I2C_readAnything(temp_6_down);
  Serial.print("Board 6: ");
  Serial.print(temp_6_up , 2); Serial.print(" | ");
  Serial.print(temp_6_middle , 2); Serial.print(" | ");
  Serial.println(temp_6_down , 2);
  Serial.println("------------------------------------------------------------");

  delay(1000);

  if (client.connect(server,80))  
          {          
           String postStr = apiKey_69;
               postStr +="&field1=";
               postStr += String(temp_6_middle);
               postStr +="&field2=";
               postStr += String(temp_6_down);
               postStr +="&field3=";
               postStr += String(temp_6_up);
               postStr += "\r\n\r\n\r\n";
            
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKapiKey_4: "+apiKey_69+"\n");
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
