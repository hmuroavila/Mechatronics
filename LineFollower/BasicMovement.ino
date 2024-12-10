// Defining PINS
// ENA, IN1 and IN2 are the 1st (LEFT) motor variables
// ENB, IN3 and IN4 are the 2nd (RIGHT) motor variables
#define ENA 31
#define ENB 33
#define IN1 2
#define IN2 25
#define IN3 27
#define IN4 3

// Digital INPUT pins for measuring distance
#define LOutA 22
#define LOutB 24
#define ROutA 26
#define ROutB 28

// New speed values for Line following in other folder

void MovementSetup() {
  // INitialize all pins
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

// Line Foward for things
void LineForward(){
    // Left 1 Motor things
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, LeftSpeed);
    digitalWrite(IN2, LOW);

    // Right 2 Motor things
    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, RightSpeed);
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


/*
void cmForward(int x)
{
  // 188.5 mm  * (1 cm / 10 mm) * (500 count / 30 cm) = 314 count per 1 rotation or 16 count per 1 cm
  // reset count
  noInterrupts();
  counter = 0;
  countCheck = true;
  countToTravel = (int)( (float)x * 16.0);
  interrupts();
  Forward();
}
 
void cmReverse(int x)
{
  noInterrupts();
  counter = 0;
  countCheck = true;
  countToTravel = (int)( (float)x * 16.0);
  interrupts();
  Reverse();
}

*/
/*
// Interrupt services (Part 2)
void interruptRising()
{
  // Whenever a rising edge from LEFT motor is detected on OutputA, we call this function
  // It will add to the appropriateCOUNT
  counter++;

  if((countCheck == true) && (counter >= countToTravel))
  {
    Brake();
    countCheck = false;
  }
}



void interruptFalling()
{
  counter++;

  if((countCheck == true) && (counter >= countToTravel))
  {
    Brake();
    countCheck = false;

  }

}

*/



