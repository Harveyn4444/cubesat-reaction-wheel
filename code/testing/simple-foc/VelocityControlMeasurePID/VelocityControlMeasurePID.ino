/*******************************

Velocity PID Control and Measure

Written by Harvey Nixon 19/04/2024


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
float motor_velocity;
float prev_motor_velocity;
float filtered_prev_motor_velocity;
float motor_angle; 
int recordNumber = 0;
uint32_t Time;
uint32_t prevTime;
uint32_t MeasureTime;
float dt;
float d_omega;
float alpha;

float target_torque = 0.1899; // This is omega_Reference

float Ix = 2.4; // Interia of wheel and motor system

//PID
float Kp =  1.0;
float Ki = 30.0;
float Kd =  0.0;
float P;
float I;
float D;

float error_velocity;
float previous_error_velocity;
float integral;
float PID_output = 20;

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

  sensor.update();

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
 // motor.controller = MotionControlType::torque;
  //motor.controller = MotionControlType::velocity_openloop;

  // set the torque control type
  motor.phase_resistance = 5.7; // 12.5 Ohms
  motor.torque_controller = TorqueControlType::voltage;
  // set motion control loop to be used
  motor.controller = MotionControlType::torque;



  // controller configuration based on the control type 
  // velocity PID controller parameters
  // default P=0.5 I = 10 D =0
  motor.PID_velocity.P = 1;
  motor.PID_velocity.I = 10.0;
  motor.PID_velocity.D = 0.0;
  
  // jerk control using voltage voltage ramp
  // default value is 300 volts per sec  ~ 0.3V per millisecond
  motor.PID_velocity.output_ramp = 1000;


  // velocity low pass filtering
  // default 5ms - try different values to see what is the best. 
  // the lower the less filtered
//  motor.LPF_velocity.Tf = 0.01;
  motor.LPF_velocity.Tf = 0.5;

  // since the phase resistance is provided we set the current limit not voltage
  // default 0.2
  motor.current_limit = 1; // Amps

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

  //Serial.begin(115200);
  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  //delay(1000);

  //motor.loopFOC();

  // Serial.print("Target");Serial.print("\t");
  // // display the angle and the angular velocity to the terminal
  // Serial.print("Measured");
  // Serial.print("\t");
  // Serial.println("Angle");
  MeasureTime = millis();
} // END of Setup()

void loop() {

  // open loop velocity movement
  // using motor.voltage_limit and motor.velocity_limit
  // to turn the motor "backwards", just set a negative target_velocity
  Time = millis() - MeasureTime;
// testing running for 300 ms then doing the main loop and printing

  if (Time < 5000){  
  // main FOC algorithm function
  motor.loopFOC();

  // Motion control function
  //motor.move(target_velocity);
  motor.move(target_torque);
  //motor.loopFOC();
  //motor.move(target_velocity);
  //motor.move(PID_output);

  sensor.update();
  motor_velocity = sensor.getVelocity();
  
  // Apply low-pass filtering
  filteredValue = (filteredValue * (1 - RC)) + (motor_velocity * RC);

//PLACEMENT OF THIS IS IMPORTANT - THIS IS A GUESS/START
  dt = (Time) - (prevTime);
  //Serial.println(dt,6); 
  //d_omega = motor_velocity - prev_motor_velocity;
  d_omega = filteredValue - filtered_prev_motor_velocity;

  alpha = d_omega / (dt,4) ;
  //Serial.println(alpha);
  //prev_motor_velocity = motor_velocity;
  filtered_prev_motor_velocity = filteredValue;
  //using this to determine the refreence torque required at each point for a set "speed" for the example the target speed is 20 rads-1



  motor_angle = sensor.getAngle();
  //  error_velocity = target_velocity - motor_velocity;
  error_velocity = target_velocity - filteredValue;  

  // //Proportional 
  // P = Kp * error_velocity;
  
  // //Integral
  // integral += error_velocity;
  // I = Ki * integral;

  // //Derivative
  // D = Kd * (error_velocity - previous_error_velocity);
  // previous_error_velocity = error_velocity;

  // PID_output = P + I + D;
  //Serial.println();
  //Serial.println(PID_output); // So we would do motor.move(PID_output)

  Serial.print(Time);Serial.print(",");
  Serial.print(target_velocity);Serial.print(",");
  Serial.print(target_torque,4);Serial.print(",");
  Serial.print(filteredValue);Serial.print(",");
  Serial.print(error_velocity);Serial.print(",");
  //Serial.println(error_velocity);
  Serial.print(alpha,4);Serial.print(",");
  Serial.println((alpha * Ix), 4);


  // user communication
  command.run();

  recordNumber = recordNumber + 1;

  delay(1);
  //delayNanoseconds(1);
  prevTime = Time;
  }
} // END of Loop()
