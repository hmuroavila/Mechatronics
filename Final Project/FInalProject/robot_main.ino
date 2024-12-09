#include <Servo.h>

#define distSnsr A0
#define servoPin 12 // change pin number as needed

#define initalServoPosition 180 // can change inital servo position between 0 and 180 (center at 90)
#define wall1Dist 10 // in cm
#define wall2Dist 10 // in cm
#define wall3Dist 10 // in cm
#define wall4Dist 10 // in cm
#define quartersBackStage1 5 // in cm
#define quartersBackStage2 10 // in cm
#define distanceToQuarters 2 // in cm
#define hitButtonDist 1 // in cm

Servo myServo;

bool onButton = FALSE;
bool lineStage1 = FALSE;
bool lineStage2 = FALSE;
bool lineStage3 = FALSE;
bool lineStage4 = FALSE;
bool quartersStage1 = FALSE;
bool quartersStage2 = FALSE;
bool hitButtonStage = FALSE;


void setup() {
  Serial.println(9600);

  driveSetup();

  pinMode(distSnsr, INPUT);

  myServo.attach(servoPin);
  myServo.write(initialServoPosition);
}

void loop() {
  readButton();

  while (readButton()) {
    Forward();

    if((readDistance() < wall1Dist) && (lineStage1 == FALSE) && (lineStage2 == FALSE) && (lineStage3 == FALSE) && (lineStage4 == FALSE) && (quartersStage1 == FALSE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(wall1Dist - readDistance()); // adjust to corner
      pivotRight(); // pivot right
      lineStage1 = TRUE;
    }

    if((readDistance() < wall2Dist) && (lineStage1 == TRUE) && (lineStage2 == FALSE) && (lineStage3 == FALSE) && (lineStage4 == FALSE) && (quartersStage1 == FALSE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(wall2Dist - readDistance()); // adjust to corner
      pivotRight(); // pivot right
      lineStage2 = TRUE;
    }

    if((readDistance() < wall3Dist) && (lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == FALSE) && (lineStage4 == FALSE) && (quartersStage1 == FALSE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(wall3Dist - readDistance()); // adjust to corner
      pivotRight(); // pivot right
      lineStage3 = TRUE;
    }

    if((readDistance() < wall4Dist) && (lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == TRUE) && (lineStage4 == FALSE) && (quartersStage1 == FALSE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(wall4Dist - readDistance()); // adjust to corner
      pivotRight(); // pivot right
      lineStage4 = TRUE;
    }

    if((readDistance() < quartersBackStage1) && (lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == TRUE) && (lineStage4 == TRUE) && (quartersStage1 == FALSE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(quartersBackStage1 - readDistance()); // adjust to corner
      pivotLeft(); // pivot right
      cmReverse(distanceToQuarters);
      cmForward(distanceToQuarters);
      pivotRight()
      quartersStage1 = TRUE;
    }

    if((readDistance() < quartersBackStage2) && (lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == TRUE) && (lineStage4 == TRUE) && (quartersStage1 == TRUE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(quartersBackStage2 - readDistance()); // adjust to corner
      pivotLeft(); // pivot right
      cmReverse(distanceToQuarters);
      cmForward(distanceToQuarters);
      pivotRight()
      cmForward(wall4Dist - readDistance());
      quartersStage1 = TRUE;
    }

    if((readDistance() < quartersBackStage2) && (lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == TRUE) && (lineStage4 == TRUE) && (quartersStage1 == TRUE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      cmReverse(quartersBackStage2 - readDistance()); // adjust to corner
      pivotLeft(); // pivot right
      cmReverse(distanceToQuarters);
      cmForward(distanceToQuarters);
      pivotRight()
      cmForward(wall4Dist - readDistance());
      pivotLeft();
      quartersStage1 = TRUE;
    }

    if((readDistance() < hitButtonDist) && (lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == TRUE) && (lineStage4 == TRUE) && (quartersStage1 == TRUE) && (quartersStage2 == FALSE) && (hitButtonStage == FALSE)) {
      int buttonTravelDist = hitButtonDist - readDistance();
      cmForward(buttonTravelDist);
      cmReverse(buttonTravelDist);
      hitButtonStage = TRUE;
    }

    if((lineStage1 == TRUE) && (lineStage2 == TRUE) && (lineStage3 == TRUE) && (lineStage4 == TRUE) && (quartersStage1 == TRUE) && (quartersStage2 == FALSE) && (hitButtonStage == TRUE)) {
      playGame();
    }
  }
}
