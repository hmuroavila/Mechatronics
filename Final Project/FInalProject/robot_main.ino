#include <Servo.h>
#define distSnsr A0
#define servoPin 12 // change pin number as needed

#define initalServoPosition 180 // can change inital servo position between 0 and 180 (center at 90)
#define initialDist 43 // in cm
#define coinDist 10 // in cm
#define backdist 10 // in cm
#define minChasis 10 // in cm
#define backButton 5 // in cm
#define greenAngle -90
#define blueAngle -60
#define whiteAngle -30
#define redAngle 30
#define purpleAngle 60
#define yellowAngle 90


Servo myServo;

bool stage1 = false;
bool stage2 = false;
bool stage3 = false;
bool stage4 = false;
bool stage5 = false;
bool stage6 = false;
bool stage7 = false;
bool stage8 = false;
bool foundLine = false



void setup() {
  Serial.println(9600);

  driveSetup();

  pinMode(distSnsr, INPUT);

  myServo.attach(servoPin);
  myServo.write(initalServoPosition);
  stage1=true;
}

void loop() {
  readButton();

  while (readButton()) {
    Forward();
    //initial forward go by 43cm vars needed. initdist stage1 stage2
    if(stage1==true && stage2==false && stage3==false && stage4==false && stage5==false && stage6==false && stage7==false && stage8==false)
    {
      cmForward(initialDist);
      stage1=false
      stage2=true
    }
    //pivot right until sense line vards needed foundline stage2 stage3
    if(stage1==false && stage2==true && stage3==false && stage4==false && stage5==false && stage6==false && stage7==false && stage8==false){
      while(foundLine == false){
        PivotRight();
        if(/*linefollower found line*/){
          foundLine=true;
          stage2=false;
          stage3=true
        }
      }
    }
    

    //follow line until dist reads 10-20cm vars needed currentdist coindist stage3 stage4
    if(stage1==false && stage2==false && stage3==true && stage4==false && stage5==false && stage6==false && stage7==false && stage8==false){
        currentDist=readDistance();
        if(currendDist<=coinDist){
          stage3=false;
          stage4=true;
        }
        else{
          //line follow forward
        }
    }

    //turn left 90 degrees vars needed backup stage4 stage5
    if(stage1==false && stage2==false && stage3==false && stage4==true && stage5==false && stage6==false && stage7==false && stage8==false){
        //turn left 90
        stage4=false;
        stage5=true;
    }

    //go forward until distance reads min chassis dist to make sure pushed button vars needed minchasis stage5 stage6
      if(stage1==false && stage2==false && stage3==false && stage4==false && stage5==true && stage6==false && stage7==false && stage8==false){
          currentDist=readDistance();
          if(currentDist <= minChasis){
            Forward();
          }
          else{
            stage5=false;
            stage6=true;
          }
      }

    //go back 59 cm vars needed whackprepdist stage6 stage7
    if(stage1==false && stage2==false && stage3==false && stage4==false && stage5==false && stage6==true && stage7==false && stage8==false){
        cmReverse(backButton);
        stage6=false;
        stage7=true
    }

    //loop for whack
    // based on color input
    // turn a certain amount of degrees
    // go forward after internal hall effect reads a min dist add in line follow
    //once dist sens reads min chasis dist stop
    //depress servo
    //retract servo
    //read color until good match
    //reverse dist until back in center 
    //reset angle
    //loop back with new color
    if(stage1==false && stage2==false && stage3==false && stage4==false && stage5==false && stage6==false && stage7==true ){

    }


   
  }
}

