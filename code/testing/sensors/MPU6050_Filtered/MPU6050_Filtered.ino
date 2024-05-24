/*************************

Measuring the gyro rates of the MPU6050 and calibrating and filtering/smoothing the data

Harvey Nixon



***************************/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float target_velocity = 0;
float gyroX;
float gyroY;
float gyroZ;
float gyroX_Filtered;
float gyroY_Filtered;
float gyroZ_Filtered;
float omega_dotX;
float omega_dotY;
float omega_dotZ;
uint32_t Time;
uint32_t MeasureTime;

// Define the time constant for the low-pass filter (RC time constant)
const float RC = 0.3;  // You may need to adjust this value based on your requirements
// Want this to smooth the data be also be reactive enough

void setup() {
  Serial.begin(115200);
  delay(1000);
  //Serial.println("MPU6050_Filtered");

  // Try to initialize!
  if (!mpu.begin(0x69)) {
    //Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  //Serial.println("MPU6050 Found!");

    MeasureTime = millis();

} // END of setup()

void loop() {
  Time = millis() - MeasureTime;
  if (Time < 5000){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    gyroX = g.gyro.x;
    gyroY = g.gyro.y;
    gyroZ = g.gyro.z;
    
    // Apply low-pass filtering
    //gyroX_Filtered = (gyroX_Filtered * (1 - RC)) + (gyroX * RC);
   // gyroY_Filtered = (gyroY_Filtered * (1 - RC)) + (gyroY * RC);
    //gyroZ_Filtered = (gyroZ_Filtered * (1 - RC)) + (gyroZ * RC);
/*
    Serial.print("RAW X: ");
    Serial.print(gyroX);
    Serial.print(", Y: ");
    Serial.print(gyroY);
    Serial.print(", Z: ");
    Serial.println(gyroZ);
    
    Serial.print("Filtered X: ");
    Serial.print(gyroX_Filtered);
    Serial.print(", Y: ");
    Serial.print(gyroY_Filtered);
    Serial.print(", Z: ");
    Serial.println(gyroZ_Filtered);
*/
    //Serial.print("RAW Z: ");
    Serial.print(Time);
    Serial.print(",");
    Serial.println(gyroZ);
    //Serial.print(",");

    //Serial.print(",Filtered Z: ");
    //Serial.println(gyroZ_Filtered);
/*
    //When tested and found the correct axis
    Serial.print(Time);Serial.print(",");
    Serial.print(target_velocity);Serial.print(",");
    Serial.print(gyroX);Serial.print(",");
    Serial.println(gyroX_Filtered);
*/
   
  }
 delay(1);
} // END of Loop()
