#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// Variables for storing previous gyro values
float prevGyroX = 0;
float prevGyroY = 0;
float prevGyroZ = 0;

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

// Variables for storing angular acceleration values
float angularAccX = 0;
float angularAccY = 0;
float angularAccZ = 0;

// Time variables
unsigned long prevTime = 0;
unsigned long currentTime = 0;

void setup() {
  Serial.begin(9600);
  
  if (!mpu.begin(0x69)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // Get current time
  currentTime = millis();
  
  // Read gyroscope data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
  
  // Convert raw data to degrees per second (dps)
   gyroX = g.gyro.x;
   gyroY = g.gyro.y;
   gyroZ = g.gyro.z;
    gyroZ_Filtered = (gyroZ_Filtered * (1 - RC)) + (gyroZ * RC);
  
  // Calculate time interval
  float dt = (currentTime - prevTime) / 1000.0; // Convert milliseconds to seconds
  
  // Calculate angular acceleration
  //angularAccX = (gyroX - prevGyroX) / dt;
  //angularAccY = (gyroY - prevGyroY) / dt;
//  angularAccZ = (gyroZ - prevGyroZ) / dt;
  angularAccZ = (gyroZ_Filtered - prevGyroZ) / dt;
  
  // Update previous gyro values and time
  //prevGyroX = gyroX;
  //prevGyroY = gyroY;
  prevGyroZ = gyroZ_Filtered;
  prevTime = currentTime;
  
  // Output angular acceleration
  //Serial.print("Angular AccX: ");
  //Serial.print(angularAccX);
  //Serial.print(",");
  //Serial.print("\tAngular AccY: ");
  //Serial.print(angularAccY);
  //Serial.print(",");
  //Serial.print("\tAngular AccZ: ");
  Serial.print(target_velocity);
  Serial.print(",");
  Serial.println(angularAccZ);
  
  delay(10); // Adjust delay as needed
}
