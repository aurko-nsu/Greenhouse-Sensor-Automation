#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Wire.h> 
#include<I2C_Anything.h>

#define buzzer 4
#define red_pin 9
#define green_pin 10
#define blue_pin 11

#define ONE_WIRE_BUS_ONE 7        //tempSen_one pin (digital/analog)
#define ONE_WIRE_BUS_TWO 6        //tempSen_one pin (digital/analog)
#define ONE_WIRE_BUS_THREE 8        //tempSen_one pin (digital/analog)

OneWire oneWire(ONE_WIRE_BUS_ONE);          //temperature sensor one
DallasTemperature sensors1(&oneWire);        //temperature sensor one

OneWire twoWire(ONE_WIRE_BUS_TWO);          //temperature sensor two
DallasTemperature sensors2(&twoWire);        //temperature sensor two

OneWire threeWire(ONE_WIRE_BUS_THREE);          //temperature sensor two
DallasTemperature sensors3(&threeWire);        //temperature sensor two


int R, G, B;
int OK = 0;
float temp_one_4;          //temperature from sensor one
float temp_one_4_value;    //temperature from sensor one
float temp_two_4;          //temperature from sensor two
float temp_two_4_value;    //temperature from sensor two
float temp_three_4;          //temperature from sensor three
float temp_three_4_value;    //temperature from sensor three

void setup() {
  Serial.begin(9600);
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(buzzer , OUTPUT);
  Wire.begin(0x04);
  Wire.onRequest(sendEvent);
}

void loop() {
  OK = 0;
  {//------------------------------------------------------Temperature 1
  temp_one_4 = tempSen_one_read(); 
      if(temp_one_4>0) OK++;
  }//------------------------------------------------------Temperature 1
  

  {//------------------------------------------------------Temperature 2
  temp_two_4 = tempSen_two_read();  
      if(temp_two_4>0) OK++;
  }//------------------------------------------------------Temperature 2


  {//------------------------------------------------------Temperature 3
  temp_three_4 = tempSen_three_read();  
      if(temp_three_4>0) OK++;
  }//------------------------------------------------------Temperature 3
   
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

    delay(1000);   
}

void sendEvent(int howMany)
{
  I2C_writeAnything(temp_one_4);
  I2C_writeAnything(temp_two_4);
  I2C_writeAnything(temp_three_4);
}



float tempSen_one_read()
{
  sensors1.requestTemperatures();
  temp_one_4_value = sensors1.getTempCByIndex(0);
  return temp_one_4_value;
}

float tempSen_two_read()
{
  sensors2.requestTemperatures();
  temp_two_4_value = sensors2.getTempCByIndex(0);
  return temp_two_4_value;
}

float tempSen_three_read()
{
  sensors3.requestTemperatures();
  temp_three_4_value = sensors3.getTempCByIndex(0);
  return temp_three_4_value;
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
