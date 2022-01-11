
//               Vacheron Constantin X EPFL                 //
unsigned long myTime;
#include <Time.h>
#include <TimeLib.h>
long ax_calib;
long ay_calib;
long az_calib;
// --------------------------------------   MPU-6050   -------------------------------------- //
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;
// --------------------------------------   SD Card   -------------------------------------- //
#include <SD.h>
#include <SPI.h>
File myFile;
#define SD_ChipSelectPin 53
// --------------------------------------   Microphone   -------------------------------------- //
#include <Boards.h>
#include <TMRpcm.h>
TMRpcm audio;
int data;
#include <Usb.h>

USB usb;

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void setup() {

Serial.begin(9600);
//setTime(12,0,0,1,1,20); 
  if(usb.Init() == -1) {
    Serial.println("Error on USB initialization");
  } else {
    Serial.println("Serial USB is CONNECTED");
  }
// --------------------------------------   MPU-6050   -------------------------------------- //
  Serial.print("Set up of MPU6050 is in progress ... ");
  
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) { delay(10); } }
  
  Serial.println("MPU6050 is set up !");
  delay(1);

// --------------------------------------   SD Card   -------------------------------------- //

  Serial.print("\nInitializing SD card... ");
  
  Serial.println("SD card is ready to use.");

  Serial.println("Writing in the sd card file ...");
  
  Serial.println("   ");
  
  pinMode(SD_ChipSelectPin, OUTPUT);
  //pinMode(A0, INPUT);
  SD.begin(SD_ChipSelectPin);
  audio.CSPin = SD_ChipSelectPin;
  
  if (SD.begin()) {
      uint16_t data= Serial.read();
      Serial.println(data);
      
    Serial.println("SD card is ready to use.");
    audio.startRecording("1.wav", 441000, data);
    Serial.println("recording in progress ...");
    
    myFile = SD.open("test.txt", FILE_WRITE);
    
    Serial.println("writing in the sd card file ...");
      if (myFile) {    
        //myFile.println("New recording");
        myFile.print("New recording / Date");
        myFile.print(" , ");
        myFile.print("Acceleration X");
        myFile.print(" , ");
        myFile.print("Acceleration Y");
        myFile.print(" , ");
        myFile.print("Acceleration Z");
        myFile.print(" , ");
        myFile.print("Rotation X");
        myFile.print(" , ");
        myFile.print("Rotation Y");
        myFile.print(" , ");
        myFile.print("Rotation Z");
        myFile.print(" , ");
        myFile.print("Temperature ");
        myFile.println(" , ");
        //Serial.println("New recording"); 
        myFile.close(); // close the file
      }
      else { Serial.println("error1 opening test.txt"); }
        delay(500);
      }

  else{ Serial.println("SD card initialization failed"); return; }


delay(1);

  //audio.startRecording("1.wav", 16000, A0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void loop() {

// --------------------------------------   MPU-6050   -------------------------------------- //
  myTime = millis();
  Serial.print("Time: ");
  //Serial.println(myTime); 
  //digitalClockDisplay();

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x + 1.35);
  Serial.print(" , ");
  Serial.print("Acceleration Y: ");
  Serial.print(a.acceleration.y + 0.20);
  Serial.print(" , ");
  Serial.print("Acceleration Z: ");
  Serial.print(a.acceleration.z - 10);
  Serial.println(" , ");
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(" , ");
  Serial.print("Rotation Y: ");
  Serial.print(g.gyro.y);
  Serial.print(" , ");
  Serial.print("Rotation Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" , ");
  Serial.print("Temperature [C°] ");
  Serial.print(temp.temperature);
  Serial.println(" , ");
  Serial.println(" ");


  myFile = SD.open("test.txt", FILE_WRITE);
 
  if (myFile) { 
    //myFile.print(" ");
    //myFile.print(myTime);
 
  myFile.print(day());
  myFile.print("/");
  myFile.print(month());
  myFile.print("/");
  myFile.print(year());
  myFile.print("/");
  myFile.print(hour());
  myFile.print(":");
if(minute() < 10){
    myFile.print('0');}
  myFile.print(minute()); 

 if(second() < 10){
    myFile.print('0');}
  myFile.print(second()); 

    myFile.print(",");   
    myFile.print(a.acceleration.x);
    myFile.print(",");
    myFile.print(a.acceleration.y);
    myFile.print(",");
    myFile.print(a.acceleration.z);
    myFile.print(",");
    myFile.print(g.gyro.x);
    myFile.print(",");
    myFile.print(g.gyro.y);
    myFile.print(",");
    myFile.print(g.gyro.z);
    myFile.print(",");
    myFile.println(temp.temperature);  
    myFile.close(); // close the file
  }
  
  else { Serial.println("error2 opening test.txt"); }
  
  delay(50);

  if (!SD.break) {
    audio.stopRecording("1.wav"); 
    Serial.println("end of recording");  
  }

}
