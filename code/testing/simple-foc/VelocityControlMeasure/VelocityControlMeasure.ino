/*******************************

Velocity Control and Measure

Written by Harvey Nixon 17/04/2024


**********************************/

// Open loop motor control example
#include <SimpleFOC.h>

BLDCMotor motor = BLDCMotor(11);
// BLDCDriver3PWM driver = BLDCDriver3PWM(pwmA, pwmB, pwmC, Enable(optional));
//BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8); // UNO Pinout
BLDCDriver3PWM driver = BLDCDriver3PWM(4, 6, 5,7); //Teensy Pinout

// Magnetic sensor instance
MagneticSensorSPI sensor = MagneticSensorSPI(10, 14, 0x3FFF);

// Current Sensor
InlineCurrentSense current_sense = InlineCurrentSense(0.01f, 50.0f, A0, A2);

//target variable
float target_velocity = 20; // This is omega_Reference
float filteredValue;
float error_velocity;
float motor_velocity;
float motor_angle; 
int recordNumber = 0;
uint32_t Time;
uint32_t MeasureTime;

// instantiate the commander - this allows us to chnage the refrence velocity during the program
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_velocity, cmd); }
void doLimit(char* cmd) { command.scalar(&motor.voltage_limit, cmd); }


// Define the time constant for the low-pass filter (RC time constant)
const float RC = 0.1;  // You may need to adjust this value based on your requirements


void setup() {
  Time = millis();
  SPI.begin();
    // initialise magnetic sensor hardware
  sensor.init();
  // link the motor to the sensor
  motor.linkSensor(&sensor);

  // driver config
  SimpleFOCDebug::enable(&Serial);
  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12;
  // limit the maximal dc voltage the driver can set
  // as a protection measure for the low-resistance motors
  // this value is fixed on startup
  //driver.voltage_limit = 3;
  driver.init();
  motor.linkDriver(&driver);


  // set motion control loop to be used
  //motor.controller = MotionControlType::velocity;
    motor.controller = MotionControlType::velocity_openloop;

  // use monitoring with serial 
  Serial.begin(115200);
  // comment out if not needed
  motor.useMonitoring(Serial);

  // init motor hardware
  motor.init();
    // align sensor and start FOC
  motor.initFOC();

  // add target command T
  command.add('T', doTarget, "target velocity");
  command.add('L', doLimit, "voltage limit");

  Serial.begin(115200);
  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");


  delay(1000);
  Serial.print("Target");Serial.print("\t");
  // display the angle and the angular velocity to the terminal
  Serial.print("Measured");
  Serial.print("\t");
  Serial.println("Angle");
  MeasureTime = millis();
} // END of Setup()

void loop() {
   // motor.loopFOC();
  // open loop velocity movement
  // using motor.voltage_limit and motor.velocity_limit
  // to turn the motor "backwards", just set a negative target_velocity

  Time = millis() - MeasureTime;
  if (Time < 5000){
  motor.move(target_velocity);

  sensor.update();
  motor_velocity = sensor.getVelocity();

    // Apply low-pass filtering
  filteredValue = (filteredValue * (1 - RC)) + (motor_velocity * RC);



  motor_angle = sensor.getAngle();
  error_velocity = target_velocity - motor_velocity;

  // Print tab when testing, comma for data logging
  //Serial.print(recordNumber);
  Serial.print(Time);
  //Serial.print("\t");
  Serial.print(",");
  Serial.print(target_velocity);
  //Serial.print("\t");
  Serial.print(",");
  
  // display the angle and the angular velocity to the terminal
  //Serial.print(motor_velocity);
    // Print the filtered value
  Serial.print(filteredValue);
  //Serial.print("\t"); 
  Serial.print(",");
  //Serial.print(error_velocity);
  Serial.println(error_velocity);
  //Serial.print("\t"); 
  //Serial.print(",");
  //Serial.println(motor_angle);

  // user communication
  command.run();

  recordNumber = recordNumber + 1;

  delay(1);
  }
} // END of Loop()
