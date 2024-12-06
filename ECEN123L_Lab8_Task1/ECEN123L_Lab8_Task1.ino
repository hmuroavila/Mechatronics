#include <QTRSensors.h>

#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7
#define LED6 8
#define LED7 9
#define LED8 10


int userInput = 0;
int wThresh;
int bThresh;
int LEDs[8] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};

// bRead and wRead are the raw values arrays
// Temp  are temporary arrays used in the for loops
uint16_t bRead[8];
uint16_t bReadTemp[8] = {0,0,0,0,0,0,0,0};
uint16_t wRead[8];
uint16_t wReadTemp[8] = {0,0,0,0,0,0,0,0};

QTRSensors qtr;
uint16_t sensors[8];

void blackCal() {
  // Must calibrate by scanning five times
  // Start off by setting the threshold to be 0, then add in the new threshold value each iteration
  // Divide by 5 at the very end
  bThresh = 0;
  for(int i=0; i <= 5; i++) {
    qtr.read(bRead);

    // If the first iteration, set temp to the first read
    if(i = 0)
    {
      for(int j = 0; j < 8; j++){
        bReadTemp[j] = bRead[j];
      }
    }
    // Otherwise, we just add the new reads to the temp array
    else{
      for(int j=0;j<8;j++) {
          bReadTemp[j] = (bRead[j] + bReadTemp[j]);
      }
    }
  }
  // Once you finish that, we average each individual line item
  for(int i = 0; i < 8; i++)
  {
    bReadTemp[i] = bReadTemp[j] / 5;
  }
  // Then we add up all the averages values, average them further
  for (int i=0; i < 8; i++) {
    bThresh = bThresh + (int) bReadTemp[i];
  }
  // Final average value
  bThresh = bThresh/8;
}

void whiteCal() {
  wThresh = 0;
  for(int i=0; i <= 5; i++) {
    qtr.read(wRead);

    // If the first iteration, set temp to the first read
    if(i = 0)
    {
      for(int j = 0; j < 8; j++){
        wReadTemp[j] = wRead[j];
      }
    }
    // Otherwise, we just add the new reads to the temp array
    else{
      for(int j=0;j<8;j++) {
          wReadTemp[j] = (wRead[j] + wReadTemp[j]);
      }
    }
  }
  // Once you finish that, we average each individual line item
  for(int i = 0; i < 8; i++)
  {
    wReadTemp[i] = wReadTemp[j] / 5;
  }
  // Then we add up all the averages values, average them further
  for (int i=0; i < 8; i++) {
    wThresh = wThresh + (int) wReadTemp[i];
  }
  // Final average value
  wThresh = wThresh/8;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDs[0], OUTPUT);
  pinMode(LEDs[1], OUTPUT);
  pinMode(LEDs[2], OUTPUT);
  pinMode(LEDs[3], OUTPUT);
  pinMode(LEDs[4], OUTPUT);
  pinMode(LEDs[5], OUTPUT);
  pinMode(LEDs[6], OUTPUT);
  pinMode(LEDs[7], OUTPUT);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5,A6,A7});

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Input 1 for black calibration");
  Serial.println("Input 2 for white calibration");

  if(Serial.available() > 0) {
    userInput = Serial.read();
  }

  switch(userInput) {
    case 1:
      bReadTemp = [0,0,0,0,0,0,0,0];
      bThresh = 0;
      blackCal();
      break;
    case 2:
      wReadTemp = [0,0,0,0,0,0,0,0];
      wThresh = 0;
      whiteCal();
      break;
    default:
      break;
  }


  for(i=0;i<8;i++) {
    if ((sensor[i] <= wThresh + 50) && (sensor[i] - 50 >= wThresh )) {
      digitalWrite(LEDs[i],HIGH);
    } else if () {
      digitalWrite(LEDs[i],LOW);
    }
  }

}
