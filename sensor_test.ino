#include <SPI.h>
#include <SD.h>

File Temperature_recordings; // create a file that will be stored in the SD card

// intialising the output to the SDcard and the analog inputs from the sensors.
const int CS_PIN = 10;
int sensorA = A0;
int sensorB = A1;
int sensorC = A2;
int sensorD = A3;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);

  // Check the existance of the SD card
    if (SD.begin())
  {
    Serial.println("SD CARD IS READY TO USE.");
  } 
  else
  {
    Serial.println("INTIALIZATION FAILED!!! PLEASE INSERT SD CARD.");
    return;
  }


  
}

// the loop routine runs over and over again forever:
void loop() {

double reading = 0;
double reading2 = 0;
double reading3 = 0;
double reading4 = 0;

  for(int i = 0; i < 50; i++) { // Average 10 readings for accurate reading
     reading += analogRead(sensorA); 
     reading2 += analogRead(sensorB); 
     reading3 += analogRead(sensorC); 
     reading4 += analogRead(sensorD); 
     
     delay(1);
  }

// Sensor 1
//  double SensorA = analogRead(sensorA);
  float v = reading*(5.0/1023)/50; //converts the values to voltage
  double TEMPERATURE1 = (1000/43)*v - 50; // convert the voltage values to temperature
  

// Sensor 2
//  double SensorB = analogRead(sensorB);
  float v2 = reading2*(5.0/1023)/50; //converts the values to voltage
  double TEMPERATURE2 = (1000/43)*v2 - 50; // convert the voltage values to temperature


// Sensor 3 
 // double SensorC = analogRead(sensorC);
  float v3 = reading3*(5.0/1023)/50; //converts the values to voltage
  double TEMPERATURE3 = (1000/43)*v3 - 50; // convert the voltage values to temperature


// sensor4

//  double SensorD = analogRead(sensorD);
  float v4 = reading4*(5.0/1023)/50; //converts the values to voltage
  double TEMPERATURE4 = (1000/43)*v4 - 50; // convert the voltage values to temperature


// print the voltage on the serial monitor
  Serial.print(TEMPERATURE1);   
  Serial.print(",");
  Serial.print(TEMPERATURE2);
  Serial.print(",");
  Serial.print(TEMPERATURE3);
  Serial.print(",");
  Serial.println(TEMPERATURE4); 



  delay(30000);        // delay in between reads for stability
}
