#include <ESP8266WiFi.h>
#include<I2C_Anything.h>
int minutes = 10;

int delayTime = 1000 * 60 * minutes;

String apiKey_711  = "IJ47R60WUO1FQRHA";
const char *ssid = "RoboDoc";     
const char *pass = "RoboDoc#";
const char* server = "api.thingspeak.com";
WiFiClient client;


float temp_one_11, dht_temp_11, dht_humidity_11, dht_temp2_11, dht_humidity2_11;

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
  Wire.requestFrom(0x0B, 24);
  I2C_readAnything(temp_one_11);
  I2C_readAnything(dht_temp_11);
  I2C_readAnything(dht_humidity_11);
  I2C_readAnything(dht_temp2_11);
  I2C_readAnything(dht_humidity2_11);
  Serial.print("Board 11: ");
  Serial.print(temp_one_11 , 2); Serial.print(" | ");
  Serial.print(dht_temp_11 , 2); Serial.print(" | ");
  Serial.print(dht_humidity_11 , 2); Serial.print(" | ");
  Serial.print(dht_temp2_11 , 2); Serial.print(" | ");
  Serial.println(dht_humidity2_11 , 2);
  Serial.println("------------------------------------------------------------");

  delay(1000);

  if (client.connect(server,80))   
          {          
           String postStr = apiKey_711;
               postStr +="&field1=";
               postStr += String(temp_one_11);
               postStr +="&field2=";
               postStr += String(dht_temp_11);
               postStr +="&field3=";
               postStr += String(dht_humidity_11);
               postStr +="&field4=";
               postStr += String(dht_temp2_11);
               postStr +="&field5=";
               postStr += String(dht_humidity2_11);
               postStr += "\r\n\r\n\r\n\r\n";
            
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKapiKey_4: "+apiKey_711+"\n");
           client.print("Content-Type: application/x-www-form-urlencoded\n");
           client.print("Content-Length: ");
           client.print(postStr.length());
           client.print("\n\n");
           client.print(postStr);        
           Serial.println("Send to Online Cloud.");
          }
           client.stop();

delay(delayTime);

}
