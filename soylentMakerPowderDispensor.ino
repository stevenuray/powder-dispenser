#include <Servo.h>

Servo myServo;

const int minServoRange = 600;
const int maxServoRange = 2400;
const int minBeamRange = 975;
const int maxBeamRange = 1975;
const int openDispensorPosition = 600;
const int closeDispensorPosition = 1900;
const int servoPwmPin = 9;

const int limitSwitchInputPin = A0;
const int limitSwitchPressThreshold = 600;

const int contactLightOutputPin = 13;
const int endOfCycleOutputPin = 3;

const int startDelayInMilliseconds = 1000;
const int moveToPositionDelayInMilliseconds = 13000;

const int dispenseCyclesPerLimitSwitchContact = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("START");
  myServo.attach(9);
  setupPinModes();
  closeDispensor();
}

void loop() {
  if(isLimitSwitchPressed()){
    Serial.println("LIMIT SWTICH PRESSED");
    digitalWrite(contactLightOutputPin, HIGH);
    dispenseCycle();    
  } else {    
    digitalWrite(contactLightOutputPin, LOW);
  }
  delay(5);
}

void dispenseCycle() {
  for (int i = 0; i < dispenseCyclesPerLimitSwitchContact; i++){
    digitalWrite(endOfCycleOutputPin, LOW);
    openDispensor();
    closeDispensor();
    digitalWrite(endOfCycleOutputPin, HIGH);
    delay(500);
  }
}

boolean isLimitSwitchPressed() {
  Serial.println("limitSwitchAnalogRead: " + String(analogRead(limitSwitchInputPin)));
  if(analogRead(limitSwitchInputPin) > limitSwitchPressThreshold){
    return true;
  } else {
    return false;
  }
}

void openDispensor() {
  myServo.write(openDispensorPosition);
  delay(moveToPositionDelayInMilliseconds);
}

void closeDispensor() {
  myServo.write(closeDispensorPosition);
  delay(moveToPositionDelayInMilliseconds);
}

void setupPinModes() {
  pinMode(limitSwitchInputPin, INPUT);
  pinMode(contactLightOutputPin, OUTPUT);
  pinMode(endOfCycleOutputPin, OUTPUT);
}

