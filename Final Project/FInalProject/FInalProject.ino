


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
  1 = The initial state: Do nothing until button is touched (action that transitions)
  2 = The move foward state: Becuase of the dimenension, move forwad (transision action) 
  // This will have to be distance time or just clear the line (TIME could work well to not deal with interrupts )
 3 = The line follower: Once we find the line following the line until the the distance sensor finds out that we are close to the wall (transistion action)
 3 = This is gonna be a weird hard coded bit.  We move backwards/turn/move foward do whatever we need to do in order to move past the back line, we p
 4 = probably need some sort of search algorithm that will 
  
  We can include other bits and pieces to make it work more naturally, for example a button as a beginning state with a red/green LED would be cool

*/
