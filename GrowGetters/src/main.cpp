//Libraries
#include <Arduino.h>
#include <Enes100.h>

//Pin Assignments
const int WIFI_TRANSFER = 0;
const int WIFI_RECIEVING = 1;
const int FRONT_MOTOR_R_F = 2;
const int FRONT_MOTOR_R_B = 3;
const int FRONT_MOTOR_L_F = 4;
const int FRONT_MOTOR_L_B = 5;
const int BACK_MOTOR_R_F = 6;
const int BACK_MOTOR_R_B = 7;
const int BACK_MOTOR_L_F = 8;
const int BACK_MOTOR_L_B = 9;
const int MISSION_MOTOR_F = 10;
const int MISSION_ACTUATOR_F = 11;
const int MISSION_MOTOR_B = 12;
const int MISSION_ACTUATOR_B = 13;
const int ULTRASONIC_1_TRIG = A0;
const int ULTRASONIC_1_ECHO = A1;
const int ULTRASONIC_2_TRIG = A2;
const int ULTRASONIC_2_ECHO = A3;
const int CLAW_SPEED = 11;

//Function Prototypes
void moveForward(int);
void moveBackwards(int);
void moveRight(int);
void moveLeft(int);
void turnRight(int);
void turnLeft(int);

void setup(){
  //Initializing Pins
  Enes100.begin("Grow Getters", SEED, 3, 1120, WIFI_TRANSFER, WIFI_RECIEVING);
  pinMode(WIFI_TRANSFER, OUTPUT);
  pinMode(WIFI_RECIEVING, INPUT);
  pinMode(FRONT_MOTOR_R_F, OUTPUT);
  pinMode(FRONT_MOTOR_R_B, OUTPUT);
  pinMode(FRONT_MOTOR_L_F, OUTPUT);
  pinMode(FRONT_MOTOR_R_B, OUTPUT);
  pinMode(BACK_MOTOR_R_F, OUTPUT);
  pinMode(BACK_MOTOR_R_B, OUTPUT);
  pinMode(BACK_MOTOR_L_F, OUTPUT);
  pinMode(BACK_MOTOR_L_B, OUTPUT);
  pinMode(MISSION_MOTOR_F, OUTPUT);
  pinMode(MISSION_MOTOR_B, OUTPUT);
  pinMode(MISSION_ACTUATOR_F, OUTPUT);
  pinMode(MISSION_ACTUATOR_B, OUTPUT);
  pinMode(ULTRASONIC_1_ECHO, INPUT);
  pinMode(ULTRASONIC_1_TRIG, INPUT);
  pinMode(ULTRASONIC_2_ECHO, INPUT);
  pinMode(ULTRASONIC_2_TRIG, INPUT);
  pinMode(CLAW_SPEED, OUTPUT);
}

void loop(){
}

//Functions
void moveForward(int dist){
}

void moveBackwards(int dist){
}

void moveRight(int dist){
}

void moveLeft(int dist){
}

void TurnRight(int dist){
}

void turnLeft(int dist){
}