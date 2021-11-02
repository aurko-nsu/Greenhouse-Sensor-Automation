#include <Wire.h> 
#include<I2C_Anything.h>

#define red_pin 9
#define green_pin 10
#define blue_pin 11
#define buzzer 4


#define moisture_1_SensorPin A3              
#define moisture_2_SensorPin A7              

int R, G, B;
int moisture_1, moisture_2, wet = 400, dry = 1000;          //mooisture
float moisture_1_float, moisture_2_float;
int OK = 0;


void setup() {
  Serial.begin(9600);
  pinMode(moisture_1_SensorPin, INPUT);
  pinMode(moisture_2_SensorPin, INPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(buzzer , OUTPUT);
  Wire.begin(0x08);
  Wire.onRequest(sendEvent);
}

void loop() {
  OK = 0;
  
  //---------------------------------------------------------------------------------------------Moisture 1
    moisture_1_Read(); 
    if(moisture_1>=0 && moisture_1<101) OK++;
    moisture_1_float = moisture_1 * 1.0;
  //---------------------------------------------------------------------------------------------Moisture 1

  //---------------------------------------------------------------------------------------------Moisture 2
    moisture_2_Read(); 
    if(moisture_2>=0 && moisture_2<101) OK++;
    moisture_2_float = moisture_2 * 1.0;
  //---------------------------------------------------------------------------------------------Moisture 2
    
    
    Serial.print(analogRead(moisture_1_SensorPin)); Serial.print("  |  ");
    Serial.println(analogRead(moisture_2_SensorPin));
    
      
      if(OK==2)
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
  I2C_writeAnything(moisture_1_float);
  I2C_writeAnything(moisture_2_float);
}

int moisture_1_Read()
{
  int temp = 0;
  temp = analogRead(moisture_1_SensorPin);
  moisture_1 = map(temp, wet, dry, 100, 0);
  return moisture_1;
}

int moisture_2_Read()
{
  int temp = 0;
  temp = analogRead(moisture_2_SensorPin);
  moisture_2 = map(temp, wet, dry, 100, 0);
  return moisture_2;
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
