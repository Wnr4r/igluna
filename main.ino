
// Include Libraries
#include "Arduino.h"
#include "BTHC05.h"
#include "Seeed_MCP9808.h"
#include "SparkFunLSM6DS3.h"
#include "Wire.h"

// Pin Definitions
#define BTHC05_PIN_TXD	11
#define BTHC05_PIN_RXD	10


LSM6DS3 myIMU( I2C_MODE, 0x6A ); 

// Global variables and defines

// object initialization
BTHC05 bthc05(BTHC05_PIN_RXD,BTHC05_PIN_TXD);
MCP9808  sensor;

float temp=0;
int   heartpulsedata;
float AccelX;
float AccelY;
float AccelZ;
int i;


void setup() 
{
    
    Serial.begin(9600);
    while(!Serial);
    pinMode(5, INPUT);    //L0+
    pinMode(6, INPUT);    //L0-

   if( myIMU.begin() != 0 )
  {
   //Serial.println("Device error");
  }
  else  
  {
   Serial.println("Device OK!");
  }
   if((digitalRead(5) == 1) || (digitalRead(6) == 1))
   {
    //
   }
   else
   {
   heartpulsedata = analogRead(A0);
   }
    if(sensor.init())
    {
      //
    }
    
    bthc05.begin(9600);
    bthc05.println("IGLUNA: WEARABLE HEALTH MONITORING DEVICE");
   
}

void loop() 
{
    AccelX = myIMU.readFloatAccelX();
    AccelY = myIMU.readFloatAccelY();
    AccelZ = myIMU.readFloatAccelZ();
    sensor.get_temp(&temp);
    float caltemp = temp + 1.50;
  
   //for(i = 0; i<6000; i++)
   //{
   //Serial.print(AccelX);
   //Serial.print(",");
   //Serial.print(AccelY);
   //Serial.print(",");
   //Serial.print(AccelZ);
   //Serial.print(",");
   //Serial.print(heartpulsedata);
   //Serial.print(",");
   //Serial.print(temp);
   //Serial.println(" ");
   //}
   
    //if (bthc05.available())
    //{
    bthc05.print(AccelX);
    bthc05.print(",");
    bthc05.print(AccelY);
    bthc05.print(",");
    bthc05.print(AccelZ);
    bthc05.print(",");
    bthc05.print(caltemp);
    bthc05.print(",");
    bthc05.print(heartpulsedata);
    bthc05.println(" ");

    //}
    
    
}
