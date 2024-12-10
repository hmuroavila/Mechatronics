#include <QTRSensors.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

// Define your sensor object
QTRSensors qtr;
const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// PID constants
float Kp = 0.5; // Proportional gain
float Ki = 0.1; // Integral gain
float Kd = 0.2; // Derivative gain

// PID variables apparently
float error = 0, lastError = 0, integral = 0;

// Desired position (middle vaue of 8 sensors)
float middlePoint = 3500; 

// Setup your pins and sensor
void setup() {
  Serial.begin(9600);
  // Setup the PINS and functions from the MovementScript
  MovementSetup();

  
  // Initialize the QTR sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, sensorCount);

  // Calibrate sensors steps (use light to indicate calibration)
  delay(500);
  pinMode(LED_BUILTIN,   OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i  < 200; i++)
  {
    qtr.calibrate();
  }

  digitalWrite(LED_BUILTIN, LOW);
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
      LeftSpeed = output;
    } 
    else {
      rotateRight(output);
    }
  }

  // Update last error
  lastError = error;

  delay(10); // Small delay for stability
}
