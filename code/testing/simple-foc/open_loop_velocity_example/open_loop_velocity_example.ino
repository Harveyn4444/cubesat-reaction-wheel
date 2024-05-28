// Open loop motor control example
#include <SimpleFOC.h>


// BLDC motor & driver instance
// BLDCMotor motor = BLDCMotor(pole pair number);
BLDCMotor motor = BLDCMotor(13);
// BLDCDriver3PWM driver = BLDCDriver3PWM(pwmA, pwmB, pwmC, Enable(optional));
//BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8); // UNO Pins
BLDCDriver3PWM driver = BLDCDriver3PWM(4, 6, 5,7); //Teensy Pinout

MagneticSensorSPI sensor = MagneticSensorSPI(AS5048_SPI, 10);

// Stepper motor & driver instance
//StepperMotor motor = StepperMotor(50);
//StepperDriver4PWM driver = StepperDriver4PWM(9, 5, 10, 6,  8);

InlineCurrentSense current_sense = InlineCurrentSense(0.01f, 50.0f, A0, A2);

//target variable
float target_velocity = 0;

// instantiate the commander
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_velocity, cmd); }
void doLimit(char* cmd) { command.scalar(&motor.voltage_limit, cmd); }

void setup() {

    // initialise magnetic sensor hardware
  sensor.init();
  // initialise the current sensing
  current_sense.init();
    // for SimpleFOCShield v2.01/v2.0.2
  current_sense.gain_b *= -1;

  // driver config
  // power supply voltage [V]
  driver.voltage_power_supply = 12;
  // limit the maximal dc voltage the driver can set
  // as a protection measure for the low-resistance motors
  // this value is fixed on startup
  driver.voltage_limit = 6;
  driver.init();
  // link the motor and the driver
  motor.linkDriver(&driver);

  // limiting motor movements
  // limit the voltage to be set to the motor
  // start very low for high resistance motors
  // current = voltage / resistance, so try to be well under 1Amp
  motor.voltage_limit = 3;   // [V]
 

  // current sense init hardware
  current_sense.init();
  // link the current sense to the motor
  motor.linkCurrentSense(&current_sense);

  // open loop control config
  motor.controller = MotionControlType::velocity_openloop;

  // init motor hardware
  motor.init();

  // add target command T
  command.add('T', doTarget, "target velocity");
  command.add('L', doLimit, "voltage limit");

  Serial.begin(115200);
  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  _delay(1000);
}

void loop() {

  // open loop velocity movement
  // using motor.voltage_limit and motor.velocity_limit
  // to turn the motor "backwards", just set a negative target_velocity
  motor.move(target_velocity);

    //PhaseCurrent_s currents = current_sense.getPhaseCurrents();
    float current_magnitude = current_sense.getDCCurrent();
/*
    Serial.print(currents.a*1000); // milli Amps
    Serial.print("\t");
    Serial.print(currents.b*1000); // milli Amps
    Serial.print("\t");
    Serial.print(currents.c*1000); // milli Amps
    */
    Serial.print("\t");
    //Serial.println(current_magnitude*1000); // milli Amps
    Serial.print(current_magnitude*1000); // milli Amps
    Serial.print("\t");
  
    sensor.update();
    // display the angle and the angular velocity to the terminal
    Serial.print(sensor.getAngle());
    Serial.print("\t");
    Serial.println(sensor.getVelocity());

  // user communication
  command.run();



}
