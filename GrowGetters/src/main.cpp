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

// // Global Constants
const float CM_PER_SECOND = 14.1;
const float DEGREE_PER_SECOND = 41;
const float ACTUATOR_TIME = 5;  
const float CLAW_TIME = 1;

const float SECOND_PER_CM = 1/CM_PER_SECOND;
const float SECOND_PER_DEGREE = 1/DEGREE_PER_SECOND;

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

void setup(){
  //Initializing Pins
  Enes100.begin("Grow Getters", SEED, 328, 1120, WIFI_TRANSFER, WIFI_RECIEVING);
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
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  //Reset Mission Actuator
  digitalWrite(MISSION_ACTUATOR_B, HIGH);
  delay(5000);

  //Get to mission site
  bool startPos;
  if(Enes100.getY >= 1){
    startPos = 0;
    turnTo(-90);
    delay(500);
    moveForward(100);
    delay(500);
    turnTo(-90);
  }
  else{
    startPos = 1;
    turnTo(90);
    delay(500);
    moveForward(100);
    delay(500);
    turnTo(90);
  }
  moveRight(10);
  delay(500);

  //Navigation
  moveBackwards(50);
  delay(500);
  turnTo(0);
  delay(500);
  moveForward(50);
  delay(500);
  moveLeft(100);
  delay(500);
  do{
    digitalWrite(FRONT_MOTOR_L_F, HIGH);
    digitalWrite(FRONT_MOTOR_R_B, HIGH);
    digitalWrite(BACK_MOTOR_L_B, HIGH);
    digitalWrite(BACK_MOTOR_R_F, HIGH);
  }while(readUltrasonic1() > 5 && readUltrasonic2() > 5);
  digitalWrite(FRONT_MOTOR_L_F, LOW);
  digitalWrite(FRONT_MOTOR_R_B, LOW);
  digitalWrite(BACK_MOTOR_L_B, LOW);
  digitalWrite(BACK_MOTOR_R_F, LOW);
  delay(500);
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
  float difference = (goal - (Enes100.getTheta() * 180/PI));
  if(difference > 0){
    turnLeft(difference);
  }
  else if(difference < 0){
    turnRight(-difference);
  }
}

void linearActuator(){
  static bool actuatorState;
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
  static bool clawState;
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
  return (duration / 27);
}

float readUltrasonic2(){
  digitalWrite(ULTRASONIC_2_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_2_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_2_TRIG, LOW);
 
  // Read the signal from the sensor
  float duration = pulseIn(ULTRASONIC_2_ECHO, HIGH);
  return (duration / 26.5);
}