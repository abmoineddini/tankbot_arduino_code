/*
 * Author:  Amirbahador Moineddini
 * Email:   abmoineddini@gmail.com
 * Project: Differential Drive Rover Motor Driver
 */

// Libraries
#include "ArduPID.h"


// Motor encoder output pulses per 360 degree revolution (measured manually)
#define ENC_COUNT_REV_R 180
#define ENC_COUNT_REV_L 180

// Setting Pin
#define ENC_IN_RIGHT_A 2    // right motor encoders 
#define ENC_IN_RIGHT_B 9
#define ENC_IN_LEFT_A 3     // left motor encoders 
#define ENC_IN_LEFT_B 11
const int E1 = 5;           // right motor speed (PWM)
const int M1 = 4;           // right motor direction pin
const int E2 = 6;           // left motor speed (PWM)
const int M2 = 7;           // left motor direction pin

boolean Direction_right = true;   // True = Forward; False = Reverse
boolean Direction_left = true;    // True = Forward; False = Reverse
 
// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;
volatile long left_wheel_pulse_count = 0;
 
// One-second interval for measurements
int interval = 1000;

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
float rpm_right = 0;
float rpm_left = 0;
 
// Linear velocity conversions
const float rpm_to_linear_velocity = 0.005445;  // Conversion constant
float ang_velocity_right_deg_left = 0;
float ang_velocity_right_deg_right = 0;
 
// Setting up PID Controller
ArduPID Speed_Controller_R;
double setpoint_R = 70;
double input_R;
double output_R;

ArduPID Speed_Controller_L;
double setpoint_L = 70;
double input_L;
double output_L;

double p = 0.10;
double i = 0.000015;
double d = 0.00015;

const double maxOutput = 255;
const double minOutput = 50;

const double maxKi = 255;
const double minKi = 65;

void setup() {
  Serial.begin(115200); 

  // Setting pin modes
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);

  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_LEFT_B , INPUT);

  digitalWrite(M1,HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 100);   //PWM Speed Control
  analogWrite(E2, 100);   //PWM Speed Control

  Speed_Controller_R.begin(&input_R, &output_R, &setpoint_R, p, i, d);
  Speed_Controller_R.setOutputLimits(minOutput, maxOutput);
  Speed_Controller_R.setOutputLimits(minKi, maxKi);

  Speed_Controller_L.begin(&input_L, &output_L, &setpoint_L, p, i, d);
  Speed_Controller_L.setOutputLimits(minOutput, maxOutput);
  Speed_Controller_L.setOutputLimits(minKi, maxKi);


  // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_pulse, CHANGE);
   
}
 
void loop() {
 
  // Record the time
  currentMillis = millis();
 
  // If one second has passed, print the number of pulses
  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
 
    // Calculate revolutions per minute
    rpm_right = (float)((right_wheel_pulse_count * 60 / ENC_COUNT_REV_R));
    rpm_left = (float)((left_wheel_pulse_count * 60 / ENC_COUNT_REV_L));
    ang_velocity_right_deg_right = rpm_right * rpm_to_linear_velocity;
    ang_velocity_right_deg_left = rpm_left * rpm_to_linear_velocity;
    

     
    Serial.print(" L-Pulses: ");
    Serial.print(left_wheel_pulse_count);
    Serial.print("   |   R-Pulses: ");
    Serial.println(right_wheel_pulse_count);

    Serial.print(" L-Speed: "); 
    Serial.print(rpm_left);
    Serial.print(" RPM");
    Serial.print("    |    R-Speed: ");
    Serial.print(rpm_right);
    Serial.println(" RPM");

    Serial.print(" L-PWM: ");
    Serial.print(output_L);
    Serial.print("    |    R-PWM: ");
    Serial.println(output_R);

    Serial.print(" V-L: ");
    Serial.print(ang_velocity_right_deg_left);
    Serial.print(" m/s");
    Serial.print("    |    V-R: ");
    Serial.println(ang_velocity_right_deg_right);
    Serial.print(" m/s");
    Serial.println("");
 
    right_wheel_pulse_count = 0;
    left_wheel_pulse_count = 0;
  }

  input_L = rpm_left;
  input_R = rpm_right;

  Speed_Controller_R.compute();
  Speed_Controller_L.compute();

  analogWrite(E1, int(output_R));
  analogWrite(E2, int(output_L));
  delay(1);
}
 
// Increment the number of pulses by 1
void right_wheel_pulse() {
   
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if(val == HIGH) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}

void left_wheel_pulse() {
   
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_LEFT_B);
 
  if(val == HIGH) {
    Direction_left = false; // Reverse
  }
  else {
    Direction_left = true; // Forward
  }
   
  if (Direction_left) {
    left_wheel_pulse_count++;
  }
  else {
    left_wheel_pulse_count--;
  }
}