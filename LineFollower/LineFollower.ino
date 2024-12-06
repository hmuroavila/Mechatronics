#include <QTRSensors.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

// Defining PINS
// ENA, IN1 and IN2 are the 1st (LEFT) motor variables
// ENB, IN3 and IN4 are the 2nd (RIGHT) motor variables
#define ENA 26
#define ENB 36
#define IN1 28
#define IN2 30
#define IN3 32
#define IN4 34

// Digital INPUT pins for measuring distance
#define LOutA 22
#define LOutB 23
#define ROutA 24
#define ROutB 25


// Define your sensor object
QTRSensors qtr;
const uint8_t NUM_SENSORS = 8;
uint16_t sensorValues[NUM_SENSORS];

// PID constants
float Kp = 0.5; // Proportional gain
float Ki = 0.1; // Integral gain
float Kd = 0.2; // Derivative gain

// PID variables
float error = 0, lastError = 0, integral = 0;
float setPoint = 2000; // Desired position (middle value for 6 sensors)

// Setup your pins and sensor
void setup() {
  Serial.begin(9600);

  // Init all pins
  // Motor H-Bridge Output
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Motor Sensor Inputs
  pinMode(LOutA, INPUT_PULLUP);
  pinMode(LOutB, INPUT_PULLUP);
  pinMode(ROutA, INPUT_PULLUP);
  pinMode(ROutB, INPUT_PULLUP);
  
  // Initialize the QTR sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5,A6,A7});


  // Calibrate the sensors
  for (int i = 0; i < 400; i++) {
    qtr.calibrate();
    delay(20);
  }

  
}

// Subfunctions for the sake of making later code simpler
void Left1Forward()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
void Right2Forward()
{
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Left1Reverse()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void Right2Reverse()
{
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Left1Brake()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}
void Right2Brake()
{
  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
void Left1Coast()
{
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void Right2Coast()
{
  digitalWrite(ENB, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}



// Turns on both motors in the "forward" direction.
// Given the orientation of the motors on the platform, they will likely to go in opposite directions.
void Forward()
{
  Coast();
  // Left1 Motor FORWARD
  Left1Forward();
  // Right2 Motor FORWARD
  Right2Forward();
}

// Opposite of Foward()
void Reverse()
{
  Coast();
  // Left1 Motor REVERSE
  Left1Reverse();
  // Right2 Motor REVERSE
  Right2Reverse();
}

// Hard stop function: will output HIGH to both sides of the motors in order to stop quickly
void Brake()
{
  // Left1 Motor BRAKE
  Left1Brake();
  // Right2 Motor BRAKE
  Right2Brake();
}


// Slow stop: will output LOW to both sides of the motor to execute a free run
void Coast()
{
  // Left1 Motor COAST
  Left1Coast();
  // Right2 Motor COAST
  Right2Coast();
}

void TurnRight()
{
  Coast();
  Left1Forward();
}

// Opposite of the TurnRight()
void TurnLeft()
{
  Coast();
  Right2Forward();
}

// Pivot the platform around its central axel.
// In theory, we should be able to set right  motor on REVERSE, then left  motor on FOWARD
// In practice, this will only be fixed once tank treads are in place
void PivotRight()
{

  Coast();
  Left1Forward();
  Right2Reverse();
}

// Switch motars from PivotLeft()
void PivotLeft()
{
  Coast();
  Left1Reverse();
  Right2Forward();
}


// Main loop
void loop() {
  // Read the sensor values and estimate the line position
  uint16_t position = qtr.readLineBlack(sensorValues);

  // Calculate the error
  error = setPoint - position;

  // Accumulate the integral term
  integral += error;

  // Calculate the derivative term
  float derivative = error - lastError;

  // Compute PID output
  float output = Kp * error + Ki * integral + Kd * derivative;

  // Logic to rotate or stop based on the PID output
  if (abs(error) > 100) { // Threshold for turning
    if (error > 0) {
      rotateLeft(output);
    } else {
      rotateRight(output);
    }
  } else {
    stopMotors();
  }

  // Update last error
  lastError = error;

  delay(10); // Small delay for stability
}

// Motor control functions
void rotateLeft(float speed) {
  Serial.println("Rotating Left");
  // Insert code to rotate left at given speed
}

void rotateRight(float speed) {
  Serial.println("Rotating Right");
  // Insert code to rotate right at given speed
}

void stopMotors() {
  Serial.println("Stopping");
  // Insert code to stop motors
}