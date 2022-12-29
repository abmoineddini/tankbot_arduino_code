# tankbot_arduino_code
The Arduino codes used for in the tankbot.

## Motor_Driver:
Motor driver is the arduino code for the Arduino to drive the motor. For this driving the BLDC on board motors, I am using a TMC260 Stepper Motor Driver Shield For Arduino with a standard Arduino UNO. I am using the EMG30 BLDC motor. Pin 5, 4, 6 and 7 are default pins set by the arduino shild for motor speed and motor direction. The Motor driver shield data sheet is availble [here](https://wiki.dfrobot.com/TMC260_Stepper_Motor_Driver_Shield_SKU__DRI0035 "BLDC sheild").
Arduino Pin Assignment is as follows:
|Pin name|Pin number|     
|----|-----|  
|Motor speed (PWM) right wheel|5(default)|
|----|-----| 
|Motor Direction right wheel|4(default)| 
|----|-----|  
|encoder A right wheel|2(interrupt)|
|----|-----| 
|encoder B right wheel|9|
|----|-----| 
|Motor speed (PWM) left wheel|6(default)|
|----|-----| 
|Motor Direction left wheel|7(default)|  
|----|-----| 
|encoder A left wheel|3(interrupt)|
|----|-----| 
|encoder B left wheel|10|


## Robot_Controller_Joy_Stick:
The arduino code for the joy stick for the controlling the robot. For this project part of the project I am using the Adeept Remote Control Shield V2.0 along with the Arduino NANO IoT 33. The Arduino NANO IoT 33 was chosen because of its bluethooth and Wifi on board and the pins are exactly the same as the Arduino nano which this shield was originally designed for. 

