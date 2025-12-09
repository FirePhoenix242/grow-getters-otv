//Libraries
#include <Arduino.h>
#include <Enes100.h>

//Pin Assignments
const int WIFI_TRANSFER = 1;
const int WIFI_RECIEVING = 0;
const int FRONT_MOTOR_R_F = 2;
const int FRONT_MOTOR_R_B = 3;
const int BACK_MOTOR_R_F = 4;
const int BACK_MOTOR_R_B = 5;
const int FRONT_MOTOR_L_F = 7;
const int FRONT_MOTOR_L_B = 6;
const int BACK_MOTOR_L_F = 9;
const int BACK_MOTOR_L_B = 8;
const int MISSION_MOTOR_F = A4;
const int MISSION_ACTUATOR_F = A5;
const int MISSION_MOTOR_B = 12;
const int MISSION_ACTUATOR_B = 13;
const int ULTRASONIC_1_TRIG = A0;
const int ULTRASONIC_1_ECHO = A1;
const int ULTRASONIC_2_TRIG = A2;
const int ULTRASONIC_2_ECHO = A3;
const int CLAW_SPEED = 10;
const int SPEED = 11;

//Global Constants
const float CM_PER_SECOND = 14.1;
const float DEGREE_PER_SECOND = 41;
const float ACTUATOR_TIME = 3;  
const float CLAW_TIME = 1;
const float TOP_WALL = 1.95;
const float OBSCTACLES_1 = 0.95;
const float OBSCTACLES_2 = 1.85;
const float BAR_X = 3.27;
const float BAR_Y = 1.59;
const float END_ZONE = 4;

const float SECOND_PER_CM = 1/CM_PER_SECOND;
const float SECOND_PER_DEGREE = 1/DEGREE_PER_SECOND;

bool actuatorState = 0;
bool clawState = 0;

// Function Prototypes
void moveForward(float);
void moveBackwards(float);
void moveRight(float);
void moveLeft(float);
void turnTo(float);
void turnRight(float);
void turnLeft(float);
void linearActuator();
void claw();
float readUltrasonic1();
float readUltrasonic2();
float getDegrees();

void setup(){
  // Initializing Pins
  Enes100.begin("GrowGetters", SEED, 328, 1120, WIFI_TRANSFER, WIFI_RECIEVING);
  pinMode(FRONT_MOTOR_R_F, OUTPUT);
  pinMode(FRONT_MOTOR_R_B, OUTPUT);
  pinMode(FRONT_MOTOR_L_F, OUTPUT);
  pinMode(FRONT_MOTOR_L_B, OUTPUT);
  pinMode(BACK_MOTOR_R_F, OUTPUT);
  pinMode(BACK_MOTOR_R_B, OUTPUT);
  pinMode(BACK_MOTOR_L_F, OUTPUT);
  pinMode(BACK_MOTOR_L_B, OUTPUT);
  pinMode(MISSION_MOTOR_F, OUTPUT);
  pinMode(MISSION_MOTOR_B, OUTPUT);
  pinMode(MISSION_ACTUATOR_F, OUTPUT);
  pinMode(MISSION_ACTUATOR_B, OUTPUT);
  pinMode(ULTRASONIC_1_ECHO, INPUT);
  pinMode(ULTRASONIC_1_TRIG, OUTPUT);
  pinMode(ULTRASONIC_2_ECHO, INPUT);
  pinMode(ULTRASONIC_2_TRIG, OUTPUT);
  pinMode(CLAW_SPEED, OUTPUT);
  pinMode(SPEED, OUTPUT);
}

void loop() {
  //Reset Mission Actuator
  digitalWrite(MISSION_ACTUATOR_B, HIGH);
  delay(3000);
  digitalWrite(MISSION_ACTUATOR_B, LOW);
  delay(500);

  //Get to mission site
  if(Enes100.getY() >= 1){
    turnTo(-90);
    for(int n = 0; n < 10; n++){
      moveForward(10);
      if(getDegrees() > -85 || getDegrees() < -95){
        delay(500);
        turnTo(-90);
      }
    }
  }
  else{
    turnTo(90);
    delay(500);
    for(int n = 0; n < 10; n++){
      moveForward(10);
      if(getDegrees() > 95 || getDegrees() < 85){
        delay(500);
        turnTo(90);
      }
    }
  }
  delay(500);
  moveRight(20);
  delay(500);
  moveForward(20);
  delay(1000);

  //Mission Code
  char orzoPlot = 'A';
  bool plotFound = 0;
  moveBackwards(3.5);
  delay(500);
  moveLeft(7);
  int n = 0;
  do{
    delay(500);
    if(Enes100.MLGetPrediction(2) == 1){
      Enes100.print("The Orzo is in plot ");
      Enes100.println(orzoPlot);
      claw();
      plotFound = 1;
    }
    else
      orzoPlot++;
    n++;
    switch(n){
      case(1):
        moveRight(7);
        break;
      case(2):
        moveBackwards(7);
        delay(500);
        moveLeft(7);
        break;
      case(3):
        moveRight(7);
        break;
    }
    delay(500);
  }while(plotFound == 0);

  //Obstacle Navigation
  moveBackwards(50);
  delay(500);
  turnTo(0);
  delay(500);
  while(Enes100.getX() < OBSCTACLES_1){
    moveForward(1);
    if(getDegrees() > 5 || getDegrees() < -5){
        delay(500);
        turnTo(0);
    }
  }
  delay(500);
  int obstacle = 1;
  bool firstClear;
  for(int n = 0; n < 2; n++){
    while(Enes100.getY() < (TOP_WALL - 0.01)){
      moveLeft(1);
      if(getDegrees() > 5 || getDegrees() < -5){
        delay(500);
        turnTo(0);
      }
    }
    delay(500);
    moveRight(20);
    delay(500);
    if(!(readUltrasonic1() <= 100 && readUltrasonic2() <= 100))
      firstClear = 1;
    while(readUltrasonic1() <= 100 && readUltrasonic2() <= 100){
      moveRight(1);
      if(getDegrees() > 5 || getDegrees() < -5){
        delay(500);
        turnTo(0);
      }
    }
    if(firstClear != 1)
      moveRight(25);
    firstClear = 0;
    delay(500);
    while(Enes100.getX() < OBSCTACLES_2 && obstacle == 1){
      moveForward(1);
      if(getDegrees() > 5 || getDegrees() < -5){
        delay(500);
        turnTo(0);
      }
    }
    delay(500);
    turnTo(0);
    obstacle = 2;
    delay(500);
  }

  //Final Navigation
  while(Enes100.getX() < BAR_X){
    moveForward(1);
  }
  delay(500);
  if(Enes100.getY() < BAR_Y){
    while(Enes100.getY() < BAR_Y){
      moveLeft(1);
    }
  }
  else{
    while(Enes100.getY() > BAR_Y){
      moveRight(1);
    }
  }
  turnTo(0);
  delay(500);
  while(Enes100.getX() < END_ZONE){
    moveForward(1);
  }


  //Victory Dance
  while(1 == 1){
    digitalWrite(FRONT_MOTOR_L_F, HIGH);
    digitalWrite(FRONT_MOTOR_R_B, HIGH);
    digitalWrite(BACK_MOTOR_L_F, HIGH);
    digitalWrite(BACK_MOTOR_R_B, HIGH);
    linearActuator();
  }

  exit(0);
}

//Functions
void moveForward(float dist){
  float time = (dist * SECOND_PER_CM * 1000);
  digitalWrite(FRONT_MOTOR_L_F, HIGH);
  digitalWrite(FRONT_MOTOR_R_F, HIGH);
  digitalWrite(BACK_MOTOR_L_F, HIGH);
  digitalWrite(BACK_MOTOR_R_F, HIGH);
  delay(time);
  digitalWrite(FRONT_MOTOR_L_F, LOW);
  digitalWrite(FRONT_MOTOR_R_F, LOW);
  digitalWrite(BACK_MOTOR_L_F, LOW);
  digitalWrite(BACK_MOTOR_R_F, LOW);
}

void moveBackwards(float dist){
  float time = (dist * SECOND_PER_CM * 1000);
  digitalWrite(FRONT_MOTOR_L_B, HIGH);
  digitalWrite(FRONT_MOTOR_R_B, HIGH);
  digitalWrite(BACK_MOTOR_L_B, HIGH);
  digitalWrite(BACK_MOTOR_R_B, HIGH);
  delay(time);
  digitalWrite(FRONT_MOTOR_L_B, LOW);
  digitalWrite(FRONT_MOTOR_R_B, LOW);
  digitalWrite(BACK_MOTOR_L_B, LOW);
  digitalWrite(BACK_MOTOR_R_B, LOW);
}

void moveRight(float dist){
  float time = (dist * SECOND_PER_CM * 1000);
  digitalWrite(FRONT_MOTOR_L_F, HIGH);
  digitalWrite(FRONT_MOTOR_R_B, HIGH);
  digitalWrite(BACK_MOTOR_L_B, HIGH);
  digitalWrite(BACK_MOTOR_R_F, HIGH);
  delay(time);
  digitalWrite(FRONT_MOTOR_L_F, LOW);
  digitalWrite(FRONT_MOTOR_R_B, LOW);
  digitalWrite(BACK_MOTOR_L_B, LOW);
  digitalWrite(BACK_MOTOR_R_F, LOW);
}

void moveLeft(float dist){
  float time = (dist * SECOND_PER_CM * 1000);
  digitalWrite(FRONT_MOTOR_L_B, HIGH);
  digitalWrite(FRONT_MOTOR_R_F, HIGH);
  digitalWrite(BACK_MOTOR_L_F, HIGH);
  digitalWrite(BACK_MOTOR_R_B, HIGH);
  delay(time);
  digitalWrite(FRONT_MOTOR_L_B, LOW);
  digitalWrite(FRONT_MOTOR_R_F, LOW);
  digitalWrite(BACK_MOTOR_L_F, LOW);
  digitalWrite(BACK_MOTOR_R_B, LOW);
}

void turnRight(float angle){
  float time = (angle * SECOND_PER_DEGREE * 1000);
  digitalWrite(FRONT_MOTOR_L_F, HIGH);
  digitalWrite(FRONT_MOTOR_R_B, HIGH);
  digitalWrite(BACK_MOTOR_L_F, HIGH);
  digitalWrite(BACK_MOTOR_R_B, HIGH);
  delay(time);
  digitalWrite(FRONT_MOTOR_L_F, LOW);
  digitalWrite(FRONT_MOTOR_R_B, LOW);
  digitalWrite(BACK_MOTOR_L_F, LOW);
  digitalWrite(BACK_MOTOR_R_B, LOW);
}

void turnLeft(float angle){
  float time = (angle * SECOND_PER_DEGREE * 1000);
  digitalWrite(FRONT_MOTOR_L_B, HIGH);
  digitalWrite(FRONT_MOTOR_R_F, HIGH);
  digitalWrite(BACK_MOTOR_L_B, HIGH);
  digitalWrite(BACK_MOTOR_R_F, HIGH);
  delay(time);
  digitalWrite(FRONT_MOTOR_L_B, LOW);
  digitalWrite(FRONT_MOTOR_R_F, LOW);
  digitalWrite(BACK_MOTOR_L_B, LOW);
  digitalWrite(BACK_MOTOR_R_F, LOW);
}

void turnTo(float goal){
  float difference = (goal - getDegrees());
  if(difference > 0){
    turnLeft(difference);
  }
  else if(difference < 0){
    turnRight(-difference);
  }
}

void linearActuator(){
  if(actuatorState != 1){
      digitalWrite(MISSION_ACTUATOR_F, HIGH);
      delay(ACTUATOR_TIME * 1000);
      digitalWrite(MISSION_ACTUATOR_F, LOW);
      actuatorState = 1;
  }
  else{
      digitalWrite(MISSION_ACTUATOR_B, HIGH);
      delay(ACTUATOR_TIME * 1000);
      digitalWrite(MISSION_ACTUATOR_B, LOW);
      actuatorState = 0;
  }
}

void claw(){
  if(clawState != 1){
      digitalWrite(MISSION_MOTOR_F, HIGH);
      delay(CLAW_TIME * 1000);
      digitalWrite(MISSION_MOTOR_F, LOW);
      clawState = 1;
  }
  else{
      digitalWrite(MISSION_MOTOR_B, HIGH);
      delay(CLAW_TIME * 1000);
      digitalWrite(MISSION_MOTOR_B, LOW);
      clawState = 0;
  }
}

float readUltrasonic1(){
  digitalWrite(ULTRASONIC_1_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_1_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_1_TRIG, LOW);
 
  // Read the signal from the sensor
  float duration = pulseIn(ULTRASONIC_1_ECHO, HIGH);
  return (duration / 54.216);
}

float readUltrasonic2(){
  digitalWrite(ULTRASONIC_2_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_2_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_2_TRIG, LOW);
 
  // Read the signal from the sensor
  float duration = pulseIn(ULTRASONIC_2_ECHO, HIGH);
  return (duration / 33.6);
}

float getDegrees(){
  return(Enes100.getTheta() * 180/PI);
}