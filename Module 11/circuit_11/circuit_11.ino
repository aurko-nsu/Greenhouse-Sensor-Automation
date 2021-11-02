#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Wire.h> 
#include<I2C_Anything.h>
#include "DHT.h"

#define DHTPIN 6
#define DHTPIN2 5

#define red_pin 9
#define green_pin 10
#define blue_pin 11

#define slaveAddress 11

#define DHTTYPE DHT11
#define DHTTYPE2 DHT11
#define buzzer 4

#define ONE_WIRE_BUS_ONE 8      

DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE2);

OneWire oneWire(ONE_WIRE_BUS_ONE);          //temperature sensor one
DallasTemperature sensors1(&oneWire);        //temperature sensor one


int R, G, B;
int OK = 0;
float temp_one_11;          //temperature from sensor one
float temp_one_11_value;    //temperature from sensor one

float dht_humidity_11, dht_temp_11, f;
float dht_humidity2_11, dht_temp2_11, f2;

char buffer[50];
char arr[] = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensors1.begin();
  dht.begin();
  dht2.begin();
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(buzzer , OUTPUT);
  Wire.begin(0x0B);
  Wire.onRequest(sendEvent);
}

void loop() {
  OK = 0;
  {//----------------------------------Temperature 1
  temp_one_11 = tempSen_one_read(); 
  if(temp_one_11>0) OK++;
  }//----------------------------------Temperature 1
  


  {//----------------------------------DHT Temperature
  dht_temp_11_check();  
  if(dht_temp_11>0 && dht_humidity_11>0) OK++;
  }//----------------------------------DHT Temperature

  {//----------------------------------DHT Temperature 2
  dht_temp_11_check2();
  if(dht_temp2_11>0 && dht_humidity2_11>0) OK++;
  }//----------------------------------DHT Temperature

  if(OK==3)
  {
    led_green();
  }
  else
  {
    led_red();
    digitalWrite(buzzer , HIGH); delay(200);
    digitalWrite(buzzer , LOW); delay(200);
    digitalWrite(buzzer , HIGH); delay(200);
    digitalWrite(buzzer , LOW); delay(200);
   }
}

void sendEvent(int howMany)
{
  I2C_writeAnything(temp_one_11);
  I2C_writeAnything(dht_temp_11);
  I2C_writeAnything(dht_humidity_11);
  I2C_writeAnything(dht_temp2_11);
  I2C_writeAnything(dht_humidity2_11);
}



//--------------------------------------------------


float tempSen_one_read()
{
  sensors1.requestTemperatures();
  temp_one_11_value = sensors1.getTempCByIndex(0);
  return temp_one_11_value;
}


void led_red()
{
  analogWrite(red_pin, 255);
  analogWrite(green_pin, 0);
  analogWrite(blue_pin, 0);
}

void led_green()
{
  analogWrite(red_pin, 0);
  analogWrite(green_pin, 255);
  analogWrite(blue_pin, 0);
}

void led_blue()
{
  analogWrite(red_pin, 0);
  analogWrite(green_pin, 0);
  analogWrite(blue_pin, 255);
}

void dht_temp_11_check()
{
  dht_humidity_11 = dht.readHumidity();
  dht_temp_11 = dht.readTemperature();
  f = dht.readTemperature(true);

  if (isnan(dht_humidity_11) || isnan(dht_temp_11) || isnan(f)) {
    return;
  }
  float hif = dht.computeHeatIndex(f, dht_humidity_11);
  float hic = dht.computeHeatIndex(dht_temp_11, dht_humidity_11, false);
}


void dht_temp_11_check2()
{
  dht_humidity2_11 = dht2.readHumidity();
  dht_temp2_11 = dht2.readTemperature();
  f2 = dht2.readTemperature(true);

  if (isnan(dht_humidity2_11) || isnan(dht_temp2_11) || isnan(f2)) {
    return;
  }
  float hif2 = dht2.computeHeatIndex(f2, dht_humidity2_11);
  float hic2 = dht2.computeHeatIndex(dht_temp2_11, dht_humidity2_11, false);
}
