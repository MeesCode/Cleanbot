#include <NewPing.h>

int initL = 2;
int initR = 3;
int onFwdL = 22;
int onRevL = 23;
int onFwdR = 24;
int onRevR = 25;

NewPing sonarright(28, 29, 200);
NewPing sonarfrontleft(30, 31, 200);
NewPing sonarfrontright(34, 35, 200);
NewPing sonarleft(32, 33, 200);

void setup(){
  Serial.begin(9600);
  pinMode(initL, OUTPUT);
  pinMode(initR, OUTPUT);
  pinMode(onFwdL, OUTPUT);
  pinMode(onRevL, OUTPUT);
  pinMode(onFwdR, OUTPUT);
  pinMode(onRevR, OUTPUT);
}

void loop(){
// Add looping content here
  if(SonarLeft() >= 20 && SonarRight() >= 20 && SonarFrontLeft() > 20)
    goForward(255);
  if(SonarLeft() < 20 && SonarFrontLeft() > 20)
    goRight(255);
  if(SonarRight() < 20 && SonarFrontRight() > 20)
    goLeft(255);
  if(SonarLeft() < 20 && SonarRight() < 20 && SonarFrontLeft() > 20)
    goForward(255);
  if(SonarFrontLeft() < 20 || SonarFrontRight() < 20){
    if(SonarFrontRight() < SonarFrontLeft())
      goLeft(255);
    if(SonarFrontLeft() < SonarFrontRight())
      goRight(255);
  }
  delay(50);
  //debug();
}

// preset voids, do not change anything below this line //

void goFree(int speedR, int speedL){
  digitalWrite(onFwdL, HIGH);
  digitalWrite(onRevL, LOW);
  digitalWrite(onFwdR, HIGH);
  digitalWrite(onRevR, LOW);
  if(speedL < 0){
    digitalWrite(onFwdL, LOW);
    digitalWrite(onRevL, HIGH);
    speedL *= -1;
  }
  if(speedR < 0){
    digitalWrite(onFwdR, LOW);
    digitalWrite(onRevR, HIGH);
    speedR *= -1;
  }
  analogWrite(initL, speedL);
  analogWrite(initR, speedR);
}

void goStop(){
  analogWrite(initL, 0);
  analogWrite(initR, 0);
  digitalWrite(onFwdL, LOW);
  digitalWrite(onRevL, LOW);
  digitalWrite(onFwdR, LOW);
  digitalWrite(onRevR, LOW);
}

void goBackward(int speedA){
  analogWrite(initL, speedA);
  analogWrite(initR, speedA);
  digitalWrite(onFwdL, LOW);
  digitalWrite(onRevL, HIGH);
  digitalWrite(onFwdR, LOW);
  digitalWrite(onRevR, HIGH);
}

void goForward(int speedA){
  analogWrite(initL, speedA);
  analogWrite(initR, speedA);
  digitalWrite(onFwdL, HIGH);
  digitalWrite(onRevL, LOW);
  digitalWrite(onFwdR, HIGH);
  digitalWrite(onRevR, LOW);
}

void goRight(int speedA){
  analogWrite(initL, speedA);
  analogWrite(initR, speedA);
  digitalWrite(onFwdL, LOW);
  digitalWrite(onRevL, HIGH);
  digitalWrite(onFwdR, HIGH);
  digitalWrite(onRevR, LOW);
}

void goLeft(int speedA){
  analogWrite(initL, speedA);
  analogWrite(initR, speedA);
  digitalWrite(onFwdL, HIGH);
  digitalWrite(onRevL, LOW);
  digitalWrite(onFwdR, LOW);
  digitalWrite(onRevR, HIGH);
}

int SonarFrontLeft(){
  if(int(sonarfrontleft.ping()/US_ROUNDTRIP_CM) == 0)
    return 255;
  else
    return int(sonarfrontleft.ping()/US_ROUNDTRIP_CM);
}

int SonarFrontRight(){
  if(int(sonarfrontright.ping()/US_ROUNDTRIP_CM) == 0)
    return 255;
  else
    return int(sonarfrontright.ping()/US_ROUNDTRIP_CM);
}

int SonarLeft(){
  if(int(sonarleft.ping()/US_ROUNDTRIP_CM) == 0)
    return 255;
  else
    return int(sonarleft.ping()/US_ROUNDTRIP_CM);
}

int SonarRight(){
  if(int(sonarright.ping()/US_ROUNDTRIP_CM) == 0)
    return 255;
  else
    return int(sonarright.ping()/US_ROUNDTRIP_CM);
}

void debug(){
  Serial.print("FrontLeft: ");
  Serial.print(SonarFrontLeft());
  Serial.print("FrontRight: ");
  Serial.print(SonarFrontRight());
  Serial.print(" Left: ");
  Serial.print(SonarLeft());
  Serial.print(" Right: ");
  Serial.println(SonarRight());
}

