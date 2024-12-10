bool readButton() {
  if(onButtonPin == 1) {
    onButton = true;
  } else {
    onButton = false;
  }
  return onButton;
}

float readDistance() { //uses equation to calculate distance, have 8 pieces for piecewise
  int distance = 0;
  int distSnsrVal = analogRead(distSnsr);
  float out = distSnsr * (5.0 / 1023.0);
  
  //between 40 and anything
  if(out>0&&out<.91){
    distance = -83.3*out + 116;
  }
    //between 35 and 40
    if(out>.91&&out<.97){
    distance = -83.3*out + 116;
  }
    //between 30 and 35
    if(out>=.97&&out<1.04){
    distance = -71.4*out + 104;
  }
    //between 25 and 30
    if(out>=1.04&&out<1.16){
    distance = -41.7*out + 73.3;
  }
    //between 20 and 25
    if(out>=1.16&&out<1.35){
    distance = -26.3*out + 55.5;
  }
    //between 15 and 20
    if(out>=1.35&&out<1.71){
    distance= -13.9*out + 38.8;
  }
    //between 10 and 15
    if(out>=1.71&&out<2.5){
    distance = -6.33*out + 25.8;
  }
    //between 5 and 10
    if(out>=2.5&&out<3.05){
      distance = -9.09*out + 32.7;
  }
    //shorter than 5
  if(out>=3.05){
    // Serial.println("shorter than 5");
    distance = -2.56*out + 12.8;
  }

  return distance;
}

/*
setup
#include "Wire.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

*/

void readColor() {
  float red, green, blue;
  delay(60);  // takes 50ms to read
  for(int i=0;i<5;i++) {
    tcs.getRGB(&red, &green, &blue);
    redReadings[i] = (int)red;
    blueReadings[i] = (int)blue;
    greenReadings[i] = (int)green;
  }

  redValueAvg = (redReadings[0] + redReadings[1] + redReadings[2] + redReadings[3] + redReadings[4])/5;
  greenValueAvg = (greenReadings[0] + greenReadings[1] + greenReadings[2] + greenReadings[3] + greenReadings[4])/5;
  blueValueAvg = (blueReadings[0] + blueReadings[1] + blueReadings[2] + blueReadings[3] + blueReadings[4])/5;

  Serial.print("Red avg val =");
  Serial.println(redValueAvg);
  Serial.print("Green avg val =");
  Serial.println(greenValueAvg);
  Serial.print("Blue avg val =");
  Serial.println(blueValueAvg);
}