// Global variables and shit
#include <QTRSensors.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define LOutA 2



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

// PID variables
float error = 0, lastError = 0, integral = 0;
float setPoint = 3500; // Desired position (middle value for 8 sensors)

// Interrupt things
volatile int counter;
int targetCount;

// State machine stuff is going in here.
#define buttonPin 53

// Start definding states
enum State{
  startingState,
  calibrate,
  initialForward,
  followLine1,
  followLine2,
  toInfinity,
  findColor,

  toGreen,
  toBlue,
  toWhite,
  toRed,
  toPurple,
  toYellow
};

State currentState;


void setup() {
  // Button stuff
  pinMode(buttonPin, INPUT_PULLUP);
  currentState = startingState;

  // Interrupt stuff
  noInterrupts();

  // other script setup
  MovementSetup();
  lineSetup();

}

void loop() {

  switch (currentState){
    case startingState:
      //For the starting state, pause all actions until the button is pressed, then continue to calibrate
      int buttonState = 0;
      if(buttonState == HIGH){
        currentState = calibrate;
      }

      break;

    case calibrate:
      // In this state, just run callibrate a ton!
      // Calibrate the sensors
      for (int i = 0; i < 200; i++) {
        qtr.calibrate();
      }
      currentState = initialForward;

      break;
    
    case initialForward:
      // In this step, we are moving a certain amount to try to reach outsie the box, switching turn right
      cmForward(25);
      TurnRight();
      while((qtr.readLineBlack(sensorValues) == 7000) || (qtr.readLineBlack(sensorValues) == 0))
      {
        delay(10);
      }
      Coast();
      currentState = followLine1;
      break;


    case followLine1:
      //Theoreticaly can implement a measure distance here
      // Fix this attach interrupt here on the bottom
      attachInterrupt(digitalPinToInterrupt(LOutA), interruptRising, RISING);
      while((counter / 45) <= 50)
      {
        followLine();
      }
      detachInterrupt(digitalPinToInterrupt(LOutA));   
      counter = 0;

      currentState = followLine2;
      break;

    case followLine2:
    /*
      while(measureDistance() >= 10){
        followLine();
      }
      */
      pivotLeftDegree();

      currentState = toInfinity;
      break;

    case toInfinity:
      break;



    // This section will probably be looping into each other
    case findColor:
      break;

    case toGreen:
      break;

    case toBlue:
      break;

    case toWhite:
      break;

    case toRed:
      break;

    case toPurple:
      break;
    case toYellow:
      break;
  }

}

