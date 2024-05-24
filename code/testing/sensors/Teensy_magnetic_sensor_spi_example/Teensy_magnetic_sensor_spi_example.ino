#include <SimpleFOC.h>
#include <SPI.h>
// MagneticSensorSPI(MagneticSensorSPIConfig_s config, int cs)
//  config  - SPI config
//  cs      - SPI chip select pin 
// magnetic sensor instance - SPI
//MagneticSensorSPI sensor = MagneticSensorSPI(AS5048_SPI, 10);
// alternative constructor (chipselsect, bit_resolution, angle_read_register, )
MagneticSensorSPI sensor = MagneticSensorSPI(10, 14, 0x3FFF);

void setup() {
  // monitoring port
  SPI.begin();
  Serial.begin(115200);

  // initialise magnetic sensor hardware
  sensor.init();

  Serial.println("Sensor ready");
  _delay(1000);
}

void loop() {
  // iterative function updating the sensor internal variables
  // it is usually called in motor.loopFOC()
  // this function reads the sensor hardware and 
  // has to be called before getAngle nad getVelocity
  delayMicroseconds(10);
  sensor.update();
  delayMicroseconds(10);
  // display the angle and the angular velocity to the terminal
  Serial.print(sensor.getAngle());
  Serial.print("\t");
  Serial.println(sensor.getVelocity());
  delay(500);
}
