// State machine stuff is going in here.
#define buttonPin 53

// Start definding states
enum State{,
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
}

void setup() {
  /*
  // Button stuff
  pinMode(buttonPin, INPUT_PULLUP);
  currentState = startingState;

  // Interrupt stuff
  noInterrupts();
  */

}

void loop() {
    /*

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

      break;
    
    case initialForward:
      // In this step, we are moving a certain amount to try to reach outsie the box, switching turn right
      cmForward(25);
      TurnRight();
      while((qtr.readLineBlack == 7000) || (qtr.readLineBlack == 0))
      {
        delay(10);
      }
      currentState = followLine1;
      break;


    case followLine1:
      //Theoreticaly can implement a measure distance here
      // Fix this attach interrupt here on the bottom
      attachInterrupt();
      while(measureDistanceTraveled() < 50)
      {
        followLine();
      }
      detachInterrupt();
      currentState = followLine
      break;

    case followLine2:
      while(measureDistance() > 10)
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
  */

  
}



/*
We are going to need a state machine, most likley using enum to define our actual states
Then using switch case in order to be switching between our states

We currently have 3 goals (that I know of)
Follow the line
By following the line, we should be able to kock down the coins
Once we detect we are getting near the wall, we need to go to the other black line
Hit the button
Then after that we continue with a loop where we:
  Detect tbe colo of the lights
  MOve to the relevant wack a mole and hit it
  Repeat

  Currently the devices that we need are:
  Arduino
  5V and 9V battery back
  The dual H brudge
  Two motors and their revelant feedback sensors
  The IR/distance sensor (needs to be retested)
  The color sensor, need to make sure it works
  The servo
  I believe that is all


  The states should therfore be
  1 = The initial state: Do nothing until we get a button (transistion state)
  2 = Button press -> black and white calibration, we can just use the built in functions from the QTR library ()
  3 = The move foward state: Becuase of the dimenension, move forwad (transision action is based on time) 
  // This will have to be distance time or just clear the line (TIME could work well to not deal with interrupts )
 4 = The line follower: Once we find the line following the line until the the distance sensor finds out that we are past a certain amount of time (transition)
 5 = Line follower 2.0: Once we are clear of the first wall, continue liune follwing until we reach the actual final wall.

 6 = Hard coded movement: Move backwards a bit, turn 
  
  We can include other bits and pieces to make it work more naturally, for example a button as a beginning state with a red/green LED would be cool

*/
