/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>
#include <Enes100.h>

//Pin Assignments
const int WIFI_TRANSFER = 0;
const int WIFI_RECIEVING = 1;
const int FRONT_MOTOR_R_EN = 2;
const int FRONT_MOTOR_R_PWN = 3;
const int FRONT_MOTOR_L_EN = 4;
const int FRONT_MOTOR_L_PWN = 5;
const int BACK_MOTOR_R_PWN = 6;
const int BACK_MOTOR_R_EN = 7;
const int BACK_MOTOR_L_EN = 8;
const int BACK_MOTOR_L_PWN = 9;
const int MISSION_MOTOR_PWN = 10;
const int MISSION_ACTUATOR_PWN = 11;
const int MISSION_MOTOR_EN = 12;
const int MISSION_ACTUATOR_EN = 13;
const int ULTRASONIC_1_TRIG = A0;
const int ULTRASONIC_1_ECHO = A1;
const int ULTRASONIC_2_TRIG = A2;
const int ULTRASONIC_2_ECHO = A3;
const int PROPULSION_ACTUATOR_SPEED = A4;
const int CLAW_SPEED = A5;


void setup()
{
  //Initializing pins
  Enes100.begin("Grow Getters", SEED, 3, 1120, WIFI_TRANSFER, WIFI_RECIEVING);
  pinMode(WIFI_TRANSFER, OUTPUT);
  pinMode(WIFI_RECIEVING, INPUT);
  pinMode(FRONT_MOTOR_R_EN, OUTPUT);
  pinMode(FRONT_MOTOR_R_PWN, OUTPUT);
  pinMode(FRONT_MOTOR_L_EN, OUTPUT);
  pinMode(FRONT_MOTOR_R_PWN, OUTPUT);
  pinMode(BACK_MOTOR_R_EN, OUTPUT);
  pinMode(BACK_MOTOR_R_PWN, OUTPUT);
  pinMode(BACK_MOTOR_L_EN, OUTPUT);
  pinMode(BACK_MOTOR_L_PWN, OUTPUT);
  pinMode(MISSION_MOTOR_EN, OUTPUT);
  pinMode(MISSION_MOTOR_PWN, OUTPUT);
  pinMode(MISSION_ACTUATOR_EN, OUTPUT);
  pinMode(MISSION_ACTUATOR_PWN, OUTPUT);
  pinMode(ULTRASONIC_1_ECHO, INPUT);
  pinMode(ULTRASONIC_1_TRIG, INPUT);
  pinMode(ULTRASONIC_2_ECHO, INPUT);
  pinMode(ULTRASONIC_2_TRIG, INPUT);
  pinMode(PROPULSION_ACTUATOR_SPEED, OUTPUT);
  pinMode(CLAW_SPEED, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(1000);
}