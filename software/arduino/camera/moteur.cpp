#include "moteur.h"

// constructeur par défaut
Motor::Motor(){
  
}
// init des pins et des maximums
void Motor::begin(){
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_STEP, OUTPUT);
  stepper.setMaxSpeed(400);
}
// donne les nombre de pas à faire au moteur
void Motor::rotate(int steps){
  if (direction==0){
      stepper.moveTo(steps);
    }else{
      stepper.moveTo(-steps);
    }
}
// remet le moteur à zéro
void Motor::setZero(){
  stepper.setCurrentPosition(0);
}
// set l'acceleration, la vitesse et la direction du moteur
void Motor::setParams(int speed, int acceleration, int direction){
  stepper.setAcceleration(acceleration);
  stepper.setSpeed(speed);
  this->direction=direction;
}
// renvoie vrai si le moteur n'est pas à sa position finale
boolean Motor::isRotating(){
  return stepper.distanceToGo() != 0;
}
// fait tourner le moteur
void Motor::run(){
  stepper.runSpeed();
}
// renvoie la position actuelle du moteur
int Motor::getCurrentPosition(){
  return stepper.currentPosition();
}

int Motor::timeLeft(){
  
}

int Motor::distanceLeft(){
  return stepper.currentPosition();
}

void Motor::setRotationTime(int temps_restant){
  
}

