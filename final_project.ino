#include <SPI.h>
#include <SD.h>

File Temperature_recordings; // create a file that will be stored in the SD card

// intialising the output to the SDcard and the analog inputs from the sensors.
const int CS_PIN = 10;
int sensorA = A0;
int sensorB = A1;
int sensorC = A2;
int sensorD = A3;

char filename[] = "TEMP00.csv";

void setup() {
  
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);

 // used to check if the SD card exist.
  if (SD.begin()) {
    Serial.println("SD CARD IS READY TO USE.");
  } 
  else
  {
    Serial.println("INTIALIZATION FAILED!!! PLEASE INSERT SD CARD.");
    return;
  }


// OPEN A NEW FILE FOR RECORDING THE TEMPERATURE ONTO.
 
// create a new file in root, the current working directory
  for (uint8_t i = 0; i < 100; i++) {
    filename[4] = i/10 + '0';
    filename[5] = i%10 + '0';
    if (SD.exists(filename)) {
      continue;
    }
    Temperature_recordings = SD.open(filename, FILE_WRITE);
    Temperature_recordings.print("Sensor 1,Sensor 2,Sensor 3,Sensor 4");    
    break;
  }


}



void loop() {

double reading = 0;
double reading2 = 0;
double reading3 = 0;
double reading4 = 0;

  for(int i = 0; i < 50; i++) { // Average 50 readings for accurate reading
     reading += analogRead(sensorA); 
     reading2 += analogRead(sensorB); 
     reading3 += analogRead(sensorC); 
     reading4 += analogRead(sensorD); 
     
     delay(1);
  }



/*Convert the analog voltage readings to temperature*/ 
// Sensor 1
  double TEMPERATURE1 = ((1000/43)*(reading*(5.0/1023)/50)) - 50; 
// Sensor 2
  double TEMPERATURE2 = ((1000/43)*(reading2*(5.0/1023)/50)) - 50; 
// Sensor 3 
  double TEMPERATURE3 = ((1000/43)*(reading3*(5.0/1023)/50)) - 50;
// sensor4
  double TEMPERATURE4 = ((1000/43)*(reading4*(5.0/1023)/50)) - 50; 


// print the temperature readings to the serial monitor.
  
    Serial.print(TEMPERATURE1);
    Serial.print(", ");
    Serial.print(TEMPERATURE2);
    Serial.print(", ");
    Serial.print(TEMPERATURE3);
    Serial.print(", ");
    Serial.println(TEMPERATURE4);

  // if the file is available, write to it:
 //   Temperature_recordings.println("Sensor 1,Sensor 2,Sensor 3,Sensor 4"); 
File Temperature_recordings = SD.open(filename, FILE_WRITE);
    if (Temperature_recordings){
 
    Temperature_recordings.print(TEMPERATURE1);
    Temperature_recordings.print(", ");
    Temperature_recordings.print(TEMPERATURE2);
    Temperature_recordings.print(", ");
    Temperature_recordings.print(TEMPERATURE3);
    Temperature_recordings.print(", ");
    Temperature_recordings.println(TEMPERATURE4);
    Temperature_recordings.close(); 
    }
  // check for error


  delay(30000); 

}  
