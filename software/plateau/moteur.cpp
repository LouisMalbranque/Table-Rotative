#include "moteur.h"

Motor::Motor(){
  
}
void Motor::begin(){
  stepper.setMaxSpeed(400);
}
void Motor::rotate(int steps){
  stepper.setCurrentPosition(0);
  stepper.moveTo(steps);
}
  
void Motor::setParams(int speed, int acceleration){
  stepper.setAcceleration(acceleration);
  stepper.setSpeed(speed);
}

boolean Motor::isRotating(){
  return stepper.distanceToGo() != 0;
}

void Motor::run(){
  stepper.run();
}
