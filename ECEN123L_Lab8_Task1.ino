#include <QTRSensors.h>

#define LED1 40
#define LED2 42
#define LED3 44
#define LED4 46
#define LED5 48
#define LED6 50
#define LED7 52
#define LED8 54


int userInput = 0;
int wThresh;
int bThresh;
int LEDs[8] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
uint16_t bRead[8];
uint16_t bReadTemp[8] = {0,0,0,0,0,0,0,0};
uint16_t wRead[8];
uint16_t wReadTemp[8] = {0,0,0,0,0,0,0,0};

QTRSensors qtr;
uint16_t sensors[8];

void blackCal() {
  for (int i=0; i < 5; i++) {
    qtr.read(bRead);
    for(int j=0;j<8;j++) {
      if(j=0) {
        bReadTemp[j] = bRead[j];
      } else {
        bReadTemp[j] = (bRead[j]+bReadTemp[j])/2;
      }
    }
  }

  for (int i=0; i < (8-1); i=i+2) {
    bThresh = bReadTemp[i]+bReadTemp[i+1]
  }

  bThresh = bThresh/8;
}

void whiteCal() {
  for (int i=0; i < 5; i++) {
    qtr.read(wRead);
    for(int j=0;j<8;j++) {
      if(j=0) {
        wReadTemp[j] = wRead[j];
      } else {
        wReadTemp[j] = (wRead[j]+wReadTemp[j])/2;
      }
    }
  }

  for (int i=0; i < (8-1); i=i+2) {
    bThresh = wReadTemp[i]+wReadTemp[i+1]
  }

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
      qrt.resetCalibration(); // cal black threshold
      blackCal();
      break;
    case 2:
      qrt.resetCalibration();
      whiteCal();
      break;
    default:
      break;
  }

  for(i=0;i<8;i++){
    m
  }

  for(i=0;i<8;i++) {
    if (sensor[i] > min(wThresh)) {
      digitalWrite(LEDs[i],HIGH);
    } else if () {
      digitalWrite(LEDs[i],LOW);
    }
  }

}
