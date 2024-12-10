#include <QTRSensors.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


int LeftSpeed;
int RightSpeed;

// Define your sensor object
QTRSensors qtr;
const uint8_t sensorCount = 8;
uint16_t sensorValues[sensorCount];

// PID constants
float Kp = 0.1; // Proportional gain
float Ki = 0.0; // Integral gain
float Kd = 0.0; // Derivative gain

// PID variables apparently
float error = 0, lastError = 0, integral = 0;
float setPoint = 3500; // Desired position (middle value for 8 sensors)

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

  // Calibrate the sensors
  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
  }

  digitalWrite(LED_BUILTIN, LOW);

}

// Main loop
void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  int baseSpeed = 100;
  error = setPoint - position;
  integral += error;
  float derivative = error - lastError;

  // Compute PID output
  float output = Kp * error + Ki * integral + Kd * derivative;

  LeftSpeed = constrain(baseSpeed + output, 0, 255);
  RightSpeed = constrain(baseSpeed - output, 0, 255);

  Serial.print("Error is: ");
  Serial.println(error);
  Serial.print("Output is: ");
  Serial.println(output);
  
  // Update last error
  lastError = error;
  LineForward();
  delay(10);
}
