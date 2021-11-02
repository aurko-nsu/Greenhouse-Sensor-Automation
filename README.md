# Greenhouse-Sensor-Automation
"Greenhouse Sensor Automation" it's a govt funded research project of the CEE and the Architecture Department of North South University. This project is by RoboDoc Ltd.

Measure temperatures(three layers of a plant module), moisture of the soil were the main target of this project. 
Module 4,5,6 contain three temperature sensors each. And Module 11 also contains three temperature sensors and among two of them measure humidity.

Each module contains two codes. One is for arduino microcontroller and another is for esp8266. Arduino of each module is for controlling and receive data from three temperature sensors. Arduino sends those received data to esp8266 nodemcu via I2C protocol, and then esp8266 uploads the data to cloud.

Moisture module is for measuring the moisture value of two boards' soil.  In here capacitive moisture sensor has been used to measure soil moisture. 

pulse is to control the power supply of the boards. Firstly, all the esp trigger the cloud at a time. because of that some failed to upload their data. Then I tried to differentiate the uploading time of the esp with different for loop. But that did't solve the problem of the data lossing. 
Then I re-start the whole module's power. At first one module powers up for one minute, then in the second minute another one powers up. So in the second minute two module online. Like first and second, on the third minute another module powers up. And finally on the fourth minute the last module powers up and continue all for 7 minutes. After seven minutes all the module are turned off for twenty seconds.

For cloud data storing system I have used thingspeak api.