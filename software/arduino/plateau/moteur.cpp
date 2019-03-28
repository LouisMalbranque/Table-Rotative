#include "moteur.h"

Motor::Motor(){
  
}
void Motor::begin(){
  stepper.setMaxSpeed(4000);
}
void Motor::rotate(int steps){
  stepper.moveTo(steps);
}
void Motor::setZero(){
  stepper.setCurrentPosition(0);
}
  
void Motor::setParams(int speed, int acceleration, int direction){
  stepper.setAcceleration(acceleration);
  stepper.setSpeed(speed);
}

boolean Motor::isRotating(){
  return stepper.distanceToGo() != 0;
}

void Motor::run(){
  stepper.runSpeed();
}

int Motor::getCurrentPosition(){
  return stepper.currentPosition();
}
