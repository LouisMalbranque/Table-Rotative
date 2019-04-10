#include "relays.h"
#include "bluetooth.h"

Relays::Relays(){
  
}

void Relays::begin(){
  for (int i=0; i<relays_number; i++){
    digitalWrite(pinRelay[i], LOW);
    pinMode(pinRelay[i],OUTPUT);
  }
  
  pinMode(LED,OUTPUT);
}

void Relays::triggerAll(){
  for (int i=0; i<relays_number; i++){
      
    digitalWrite(pinRelay[i], HIGH);
    digitalWrite(LED, HIGH);
    
    delay(PULSE_DURATION);
    
    digitalWrite(LED, LOW);
    digitalWrite(pinRelay[i], LOW);
    
    delay(values[PAUSE_BETWEEN_CAMERA]);
  }
}

void Relays::triggerSimultaneous(){
  for (int i=0; i<relays_number; i++){
    digitalWrite(pinRelay[i], HIGH);
  }
  delay(PULSE_DURATION);
  for (int i=0; i<relays_number; i++){
    digitalWrite(pinRelay[i], LOW);
  }
}

void Relays::setDelay(int totalDelay){
  delayBetweenTriggersMs = totalDelay - PULSE_DURATION;
}

void Relays::setValues(int *values){
  for (int i=0; i<MAXIMUM_NUMBER_OF_VALUES; i++){
    this->values[i] = values[i];
  }
  if(values[0]==0){
    relays_number = values[CAMERA_NUMBER];
    //quels relais avec appareils branchés
    setDelay(values[5]);
  }
  //Que faire en temps réel ? 
}
