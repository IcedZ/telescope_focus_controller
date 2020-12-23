/******************************************
 * Description: operate a stepper motor remotely with push buttons to remotely focus a telescope.
 * Board: Arudino Uno
 * 
 * Motor: 28BYJ-48 + Driver
 * Source: http://www.4tronix.co.uk/arduino/Stepper-Motors.php 
 * 
 * Wiring:
 * 
// This Arduino example demonstrates bidirectional operation of a
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.

Two momentary push buttons; one for CCW, one for CW rotation.
Potentiometer for setting speed.

Using momentary push buttons for on/off operation of the motor.
Set pushbutton pins to "INPUT_PULLUP"

 ******************************************/
#include <AccelStepper.h>


const int stepsPerRevolution = 32;
 
//declare variables for the motor pins
int motorPin1 = 8;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 9;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 10;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 11;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)
#define MotorInterfaceType 8
//#define maxSpeed 1200     // This will be maxspeed once I implement potentiometer
#define maxSpeed 600

// initialize the stepper library on pins 8 through 11:
// AccelStepper forwardStepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin2, motorPin3, motorPin4); // This one won't go in reverse with negative speeds.  Doesn't work.
AccelStepper myStepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
int stepCount = 0;  // number of steps the motor has taken

// Declare variables for the switch pins.
// Clockwise Pin
int cwPin = 2;
// Anti-Clockwise Pin
int ccwPin = 3;
// Speed Control Pin (potentiometer) - needs to be analog pin.
int speedPin = 4;

void setup() {
  //declare the motor pins as outputs
    // I don't think this is needed; pretty sure AccelStepper does this? Need to verify
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);

  // Set switch pins as inputs and pull-up
  pinMode(cwPin, INPUT_PULLUP);
  pinMode(ccwPin, INPUT_PULLUP);
  //pinMode(speedPin, INPUT_PULLUP);

  myStepper.setMaxSpeed(maxSpeed);
}

//////////////////////////////////////////////////////////////////////////////
void loop(){

  if (!digitalRead(cwPin)) {
    myStepper.setSpeed(maxSpeed);
    myStepper.runSpeed();
  }
  else if (!digitalRead(ccwPin)) {
    myStepper.setSpeed(maxSpeed * -1);
    myStepper.runSpeed();
  }
  else {
    delay(10);
  }
}
