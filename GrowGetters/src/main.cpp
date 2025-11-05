//Libraries
#include <Arduino.h>
#include <Enes100.h>

//Pin Assignments
const int WIFI_TRANSFER = 0;
const int WIFI_RECIEVING = 1;
const int FRONT_MOTOR_R_F = 2;
const int FRONT_MOTOR_R_B = 3;
const int BACK_MOTOR_R_F = 4;
const int BACK_MOTOR_R_B = 5;
const int FRONT_MOTOR_L_F = 6;
const int FRONT_MOTOR_L_B = 7;
const int BACK_MOTOR_L_F = 8;
const int BACK_MOTOR_L_B = 9;
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
const int MS5 = 2;

//Function Prototypes
void moveForward(float);
void moveBackwards(float);
void moveRight(float);
void moveLeft(float);
void turnRight(float);
void turnLeft(float);
void linearActuator();
void claw();
float readUltrasonic1();
float readUltrasonic2();

void ms5(int);
void ms5Sub23();
void ms5Sub458();
void ms5Sub6();

void setup(){
  //Initializing Pins
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(WIFI_TRANSFER, OUTPUT);
  pinMode(WIFI_RECIEVING, INPUT);
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
  digitalWrite(LED_BUILTIN, LOW);
  analogWrite(SPEED,100);
  digitalWrite(FRONT_MOTOR_R_F, HIGH);
  digitalWrite(FRONT_MOTOR_R_B, LOW);

  digitalWrite(BACK_MOTOR_R_F, HIGH);
  digitalWrite(BACK_MOTOR_R_B, LOW);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  digitalWrite(FRONT_MOTOR_R_F, LOW);
  digitalWrite(FRONT_MOTOR_R_B, HIGH);

  digitalWrite(BACK_MOTOR_R_F, LOW);
  digitalWrite(BACK_MOTOR_R_B, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

//Functions
void moveForward(float dist){
}

void moveBackwards(float dist){
}

void moveRight(float dist){
}

void moveLeft(float dist){
}

void turnRight(float dist){
}

void turnLeft(float dist){
}

void linearActuator(){
}

void claw(){
}

float readUltrasonic1(){
  digitalWrite(ULTRASONIC_1_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_1_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_1_TRIG, LOW);
 
  // Read the signal from the sensor
  float duration = pulseIn(ULTRASONIC_1_ECHO, HIGH);
  return (duration / 29.1);
}

float readUltrasonic2(){
  digitalWrite(ULTRASONIC_2_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_2_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_2_TRIG, LOW);
 
  // Read the signal from the sensor
  float duration = pulseIn(ULTRASONIC_2_ECHO, HIGH);
  return (duration / 29.1);
}

void ms5(int subTask){
  switch(subTask){
    case(2):
    case(3):
      ms5Sub23();
      break;
    case(4):
    case(5):
    case(8):
      ms5Sub458();
      break;
    case(6):
      ms5Sub6();
      break;
    default:
      Enes100.print("Wrong number, dumbass.");
      break;
  }
}

void ms5Sub23(){
  moveForward(350);
  delay(10000);

  for(int n = 0; n < 3; n++){
    turnRight(90);
    delay(1000);
  }
  for(int n = 0; n < 3; n++){
    turnLeft(90);
    delay(1000);
  }
}

void ms5Sub458(){
  switch(Enes100.isVisible()){
    case(true):
      Enes100.println("Current X value is: ");
      Enes100.print(Enes100.getX());
      Enes100.println("Current Y value is: ");
      Enes100.print(Enes100.getY());
      Enes100.println("Current heading value is: ");
      Enes100.print(Enes100.getTheta());
      Enes100.println("Ultrasonic 1 is reading: ");
      Enes100.print(readUltrasonic1());
      Enes100.print("cm");
      Enes100.println("Ultrasonic 2 is reading: ");
      Enes100.print(readUltrasonic2());
      Enes100.print("cm");
      delay(500);
      break;
    default:
      Enes100.println("Aruco Marker is not visible.");
      delay(1000);
      break;
  }

}

void ms5Sub6(){
  if(Enes100.getTheta() >= 0)
    turnRight(Enes100.getTheta());
  else
    turnLeft(-Enes100.getTheta());
  ms5Sub23();
}

void ms5Sub10(){
  linearActuator();
  delay(500);
  linearActuator();
}