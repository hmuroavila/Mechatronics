// Setup your pins and sensor
void lineSetup() {
  
  // Initialize the QTR sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5,A6,A7}, sensorCount);

  // On board LED for calibration step

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Calibrate the sensors
  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
  }

  digitalWrite(LED_BUILTIN, LOW);

}

// Main loop
void followLine() {
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
