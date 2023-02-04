/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD 5
  #define LEFT_MOTOR_BACKWARD  6
  #define RIGHT_MOTOR_FORWARD  9
  #define LEFT_MOTOR_FORWARD   10
  #define RIGHT_MOTOR_ENABLE 12
  #define LEFT_MOTOR_ENABLE 13

#elif defined TMC260_MOTOR_DRIVER
  #define RIGHT_MOTOR_DIREDCTION 4
  #define LEFT_MOTOR_DIREDCTION 7
  #define RIGHT_MOTOR_SPEED 5
  #define LEFT_MOTOR_SPEED 6
  #define MOTOR_ENABLE 13
  
#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
