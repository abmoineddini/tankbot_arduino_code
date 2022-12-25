/*
 * Author:  Amirbahador Moineddini
 * Email:   abmoineddini@gmail.com
 * Project: Robot Controller Joystick
 */
#include <SPI.h>

int data[10];                  // Initiating Data array
int mode =0;                   // define the mode
const int U2_Pot = 5;          // define R6
const int U1_Pot = 4;          // define R1
const int led1Pin = 6;         // define pin for LED1 which is close to NRF24L01 and used to indicate the state of NRF24L01
const int led2Pin = 7;         // define pin for LED2 which is the mode is displayed in the car remote control mode  
const int led3Pin = 8;         // define pin for LED3 which is the mode is displayed in the car auto mode
const int A_But = 2;           // define pin for D2
const int B_But = 3;           // define pin for D3
const int C_But = 4;           // define pin for D4
const int D_But = 5;           // define pin for D5
const int U1_X = 0;            // define pin for direction X of joystick U1
const int U1_Y = 1;            // define pin for direction X of joystick U1
const int U2_X = 2;            // define pin for direction X of joystick U2
const int U2_Y = 3;            // define pin for direction Y of joystick U2


void setup() {
  Serial.begin(115200);
  pinMode(led1Pin, OUTPUT);       // set led1Pin to output mode
  pinMode(led2Pin, OUTPUT);       // set led2Pin to output mode
  pinMode(led3Pin, OUTPUT);       // set led3Pin to output mode
  pinMode(A_But, INPUT_PULLUP);   // set APin to output mode
  pinMode(B_But, INPUT_PULLUP);   // set BPin to output mode
  pinMode(C_But, INPUT_PULLUP);   // set CPin to output mode
  pinMode(D_But, INPUT_PULLUP);   // set DPin to output mode
}
void loop() {
  // put the values of rocker, switch and potentiometer into the array
  data[0] = analogRead(U1_X);
  data[1] = analogRead(U1_Y);
  data[2] = analogRead(U2_X);
  data[3] = analogRead(U2_Y);
  if(digitalRead(A_But)==LOW){  
    data[4] = digitalRead(A_But);
    }else{
      data[4] = HIGH;
      }
  if( digitalRead(B_But)==LOW){
    mode = 0;
    data[5] = 0;
    data[6] = 1;
  }
  if(digitalRead(C_But)==LOW){
    mode = 1;
    data[5] = 1;
    data[6] = 0;
  }
  data[7] = digitalRead(D_But);
  data[8] = analogRead(U1_Pot);
  data[9] = analogRead(U2_Pot);

  // Mapping the outputs
  int axis_X_1 = map(data[0]-205, -210, 210, -100, 100);
  int axis_Y_1 = map(data[1]-196, -210, 210, -100, 100);
  int axis_X_2 = map(data[2]-203, -210, 210, -100, 100);
  int axis_Y_2 = map(data[3]-205, -210, 210, -100, 100);

  if(axis_X_1 <= 2 && axis_X_1 >= -2){
    axis_X_1 = 0;
  }
  if(axis_Y_1 <= 2 && axis_Y_1 >= -2){
    axis_Y_1 = 0;
  }
  if(axis_X_2 <= 2 && axis_X_2 >= -2){
    axis_X_2 = 0;
  }
  if(axis_Y_2 <= 2 && axis_Y_2 >= -2){
    axis_Y_2 = 0;
  }
  
  // Printing Data in Serial monitor
  Serial.print("Data : ");
  Serial.print(axis_X_1);
  Serial.print(", ");
  Serial.print(axis_Y_1);
  Serial.print(", ");
  Serial.print(axis_X_2);
  Serial.print(", ");
  Serial.print(axis_Y_2);
  Serial.print(", ");
  Serial.print(data[4]);
  Serial.print(", ");
  Serial.print(data[5]);
  Serial.print(", ");
  Serial.print(data[6]);
  Serial.print(", ");
  Serial.print(data[7]);
  Serial.print(", ");
  Serial.print(data[8]);
  Serial.print(", ");
  Serial.println(data[9]);
  digitalWrite(led1Pin,HIGH);
  
  // Setting LED data 
  digitalWrite(led1Pin,HIGH);             // Red LED for blinking
  delay(2);
  digitalWrite(led1Pin,LOW);
  
  if(mode==0){
    digitalWrite(led2Pin,HIGH);
    digitalWrite(led3Pin,LOW);
  }
  if(mode==1){
      digitalWrite(led2Pin,LOW);
      digitalWrite(led3Pin,HIGH);
  }
  
  delay(1000);
}
