#include <ESP8266WiFi.h>
#include<I2C_Anything.h>
int minutes = 10;

int timeDelay = 1000 * 60 * minutes;    //one loop will continue "timeDelay" mili-sec
String apiKey_58  = "I4GSSRNQWPKR55AD";
const char *ssid = "RoboDoc";
const char *pass = "RoboDoc#";
const char* server = "api.thingspeak.com";
WiFiClient client;

float temp_5_up, temp_5_middle, temp_5_down;


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
  Wire.requestFrom(0x05, 24);
  I2C_readAnything(temp_5_up);
  I2C_readAnything(temp_5_middle);
  I2C_readAnything(temp_5_down);
  Serial.print("Board 5: ");
  Serial.print(temp_5_up , 2); Serial.print(" | ");
  Serial.print(temp_5_middle , 2); Serial.print(" | ");
  Serial.println(temp_5_down , 2);
  Serial.println("------------------------------------------------------------");

  delay(1000);

  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
          {          
           String postStr = apiKey_58;
               postStr +="&field1=";
               postStr += String(temp_5_up);
               postStr +="&field2=";
               postStr += String(temp_5_middle);
               postStr +="&field3=";
               postStr += String(temp_5_down);
               postStr += "\r\n\r\n\r\n";
            
           client.print("POST /update HTTP/1.1\n");
           client.print("Host: api.thingspeak.com\n");
           client.print("Connection: close\n");
           client.print("X-THINGSPEAKapiKey_4: "+apiKey_58+"\n");
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
