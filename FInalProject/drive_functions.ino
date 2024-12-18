#include <math.h>
#include <string.h>
#include <stdio.h>


// Defining PINS
// ENA, IN1 and IN2 are the 1st (LEFT) motor variables
// ENB, IN2 and IN2 are the 2nd (RIGHT) motor variables
#define ENA 6
#define ENB 7
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11


// Digital INPUT pins for measuring distance
#define LOutA 3
#define LOutB 5
#define ROutA 2
#define ROutB 4


// Input PINS for DIP switches
#define speed1 50
#define speed2 51
#define speed3 52
#define speed4 53


// Global variables
char buffer[10];
volatile int forwardCount;
volatile int reverseCount;
int countToTravel;
volatile bool forwardCheckCount;
volatile bool reverseCheckCount;




void driveSetup() {
  // Stop interrupts to briefly set up some variables
  // Part 2 portion
/*
  noInterrupts();
  forwardCheckCount = false;
  reverseCheckCount = false;
  interrupts();
  forwardCount = 0;
  reverseCount = 0;
  countToTravel = 0;
*/
  Serial.setTimeout(60000);




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


  pinMode(speed1, INPUT);
  pinMode(speed2, INPUT);
  pinMode(speed3, INPUT);
  pinMode(speed4, INPUT);


  // Attaching interrupts to ONLY ONE wheel output
  // Part 2 section
  attachInterrupt(digitalPinToInterrupt(LOutA), interruptRising, RISING);
  attachInterrupt(digitalPinToInterrupt(LOutA), interruptFalling, FALLING);


  // Set everything else to LOW for now (aka COAST)
  Coast();
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


void cmForward(int x)
{
  // 188.5 mm  * (1 cm / 10 mm) * (500 count / 30 cm) = 314 count per 1 rotation or 16 count per 1 cm
  // reset count
  noInterrupts();
  forwardCount = 0;
  forwardCheckCount = true;
  countToTravel = (int)( (float)x * 16.0);
  interrupts();
  Forward();
}
 
void cmReverse(int x)
{
  noInterrupts();
  reverseCount = 0;
  reverseCheckCount = true;
  countToTravel = (int)( (float)x * 16.0);
  interrupts();
  Reverse();
}



/*
void loop() {  
  // Below is the command input
  Serial.println("Input your command: ");
  if(Serial.available() > 0)
  {
    // Read Serial for input, and add into a char buffer
    int inputLen = Serial.readBytesUntil(10, buffer, 10);
    Serial.print("You have input command: ");


    int number = atoi(buffer);
    Serial.println(number);
    Serial.println("");


    // Depending on the input, execute the following instructions.
    // '9' is a special sequence designed to test cmForward and cmReverse
    if(number == 1)
    {
      Forward();
    }


    else if(number == 2)
    {
      Reverse();
    }


    else if(number == 3)
    {
      Brake();
    }


    else if(number == 4)
    {
      Coast();
    }


    else if(number == 5)
    {
      TurnLeft();
    }


    else if(number == 6)
    {
      TurnRight();
    }


    else if(number == 7)
    {
      PivotLeft();
    }


    else if(number == 8)
    {
      PivotRight();
    }


    // Test procedure cmForward and cmReverse
    else if(number == 9)
    {
      cmForward(20);
      cmReverse(50);
      cmForward(30);
    }


  }  
  delay(100);
}
*/




// Interrupt services (Part 2)
void interruptRising()
{
  // Whenever a rising edge from LEFT motor is detected on OutputA, we call this function
  // It will add to the appropriateCOUNT
  delay(5);
  if(digitalRead(LOutB) == HIGH)
  {
    forwardCount++;
  }
  else if(digitalRead(LOutB) == LOW)
  {
    reverseCount++;
  }


  if((forwardCheckCount == true) && (forwardCount >= countToTravel))
  {
    Brake();
    forwardCheckCount = false;
  }
  if((reverseCheckCount == true) && (reverseCount >= countToTravel))
  {
    Brake();
    reverseCheckCount = false;
  }
}






void interruptFalling()
{
  delay(5);
  if(digitalRead(LOutB) == LOW)
  {
    reverseCount++;
  }
  else if(digitalRead(LOutB) == HIGH)
  {
    forwardCount++;
  }


  if((forwardCheckCount == true) && (forwardCount >= countToTravel))
  {
    Brake();
    forwardCheckCount = false;
  }


  if((reverseCheckCount == true) && (reverseCount >= countToTravel))
  {
    Brake();
    reverseCheckCount = false;
  }
}
