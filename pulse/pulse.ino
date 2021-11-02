#define module_4 7

#define module_5 4

#define module_6 3

#define esp_module 6

#define esp 5

#define ON_STATE HIGH
#define OFF_STATE LOW

void setup()
{
  Serial.begin(9600);
  pinMode(module_4, OUTPUT);
  pinMode(module_5, OUTPUT);
  pinMode(module_6, OUTPUT);
  pinMode(esp_module, OUTPUT);
  pinMode(esp, OUTPUT);  
}

void loop()
{
  for(int i = 0 ; i < 1000 ; i++)           //this loop will continue 60 seconds(1 minute)
  {
  digitalWrite(esp_module , ON_STATE);
  digitalWrite(esp , ON_STATE);
  
  digitalWrite(module_4 , OFF_STATE);
  digitalWrite(module_5 , OFF_STATE);
  digitalWrite(module_6 , OFF_STATE);
  delay(60);
  }
  
  for(int i = 0 ; i < 1000 ; i++)           //this loop will continue 60 seconds(1 minute)
  {
  digitalWrite(esp_module , ON_STATE);
  digitalWrite(esp , ON_STATE);
  digitalWrite(module_4 , ON_STATE);
  
  digitalWrite(module_5 , OFF_STATE);
  digitalWrite(module_6 , OFF_STATE);
  delay(60);
  }

  for(int i = 0 ; i < 1000 ; i++)           //this loop will continue 60 seconds(1 minute)
  {
  digitalWrite(esp_module , ON_STATE);
  digitalWrite(esp , ON_STATE);
  digitalWrite(module_4 , ON_STATE);
  digitalWrite(module_5 , ON_STATE);
  
  digitalWrite(module_6 , OFF_STATE);
  delay(60);
  }
  
  for(int i = 0 ; i < 1000 ; i++)           //this loop will continue 420 seconds(7 minutes)
  {
  digitalWrite(esp , ON_STATE);
  digitalWrite(esp_module , ON_STATE);
  digitalWrite(module_4 , ON_STATE);
  digitalWrite(module_5 , ON_STATE);
  digitalWrite(module_6 , ON_STATE);
  delay(420);
  }
  
  digitalWrite(esp , OFF_STATE);           //all the circuit boards will be turned off for 20 seconds
  digitalWrite(esp_module , OFF_STATE);
  digitalWrite(module_4 , OFF_STATE);
  digitalWrite(module_5 , OFF_STATE);
  digitalWrite(module_6 , OFF_STATE);
  delay(20000);

}
