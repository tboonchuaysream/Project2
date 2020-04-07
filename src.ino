/*
@author Tommy Boonchuaysream
- this is a aruduino project that is made to represent a traffic light
- there are 2 inputs and 2 outputs
*/

#include <analogWrite.h>

// the numbers of the LED pins
const int RedLED = 12;
const int GreenLED = 27;
const int BlueLED = 33;
const int WhiteLED = 32;

int pushButton = A0;

long previousMillis = 0;

//short and long timings for the traffic light
long shortInterval = 3000;
long greenInterval = 7000;
long redInterval = 7000;
long walkingInterval = 5000;

//initiate variables
String currentLight = "green";
bool walking = false;

void setup() {

  //initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  //inputs
  pinMode(pushButton, INPUT);
  //LDR
  pinMode(A2, INPUT);

  //outputs
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(WhiteLED, OUTPUT);

}

void loop() {

  unsigned long currentMillis = millis();
  //Serial.println(currentMillis);

  //reading light sensitivity level
  int sensorValue = analogRead(A2);

  //cycle between the difference light colors
  if ((currentMillis - previousMillis > redInterval) && (currentLight == "green")) {
    previousMillis = currentMillis;

    //display green
    analogWrite(RedLED, 0);
    analogWrite(GreenLED, 255);
    analogWrite(BlueLED, 0);

    currentLight = "yellow";
    
  } else if ((currentMillis - previousMillis > greenInterval) && (currentLight == "yellow")) {

    previousMillis = currentMillis;
    
    //display yellow
    analogWrite(RedLED, 255);
    analogWrite(GreenLED, 200);
    analogWrite(BlueLED, 0);

    currentLight = "red";

  } else if ((currentMillis - previousMillis > shortInterval) && (currentLight == "red")) {

    previousMillis = currentMillis;

    //display red
    analogWrite(RedLED, 255);
    analogWrite(GreenLED, 0);
    analogWrite(BlueLED, 0);

    currentLight = "green";

  } else if (walking == true) {
    
    currentLight = "white";

    //display red
    analogWrite(RedLED, 255);
    analogWrite(GreenLED, 0);
    analogWrite(BlueLED, 0);

    if (currentMillis - previousMillis < walkingInterval) {

      //blinking white light
      analogWrite(WhiteLED, 255);
      delay(1000);
      analogWrite(WhiteLED, 0);
      delay(1000);
      analogWrite(WhiteLED, 255);
      delay(1000);

    } else {

      currentLight = "green";
      walking = false;
      analogWrite(WhiteLED, 0);
      
    }

  }

  int buttonState = digitalRead(pushButton);

  //check if the switch was pressed
  if (buttonState == 1) {
    
    previousMillis = currentMillis;
    walking = true;

  }

  //check if it's night time
  //if yes, decrease the duration of the red light
  if (sensorValue < 500) {

    redInterval = 3000;

  } else if (sensorValue >= 500) {

    redInterval = 7000;

  }

}
