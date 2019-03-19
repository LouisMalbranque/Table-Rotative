#include "relays.h"
#include "bluetooth.h"

Relays::Relays(){
  
}

void Relays::begin(){
  for (int i=0; i<PULSE_DURATION; i++){
    digitalWrite(pinRelay[i], LOW);
  }
}

void Relays::triggerAll(){
  for (int i=0; i<relays_number; i++){
      
    digitalWrite(pinRelay[i], HIGH);
    digitalWrite(3, HIGH);


    delay(PULSE_DURATION);
    digitalWrite(3, LOW);
    digitalWrite(pinRelay[i], LOW);
    delay(delayBetweenTriggersMs);
  }
  digitalWrite(2, HIGH);


    delay(PULSE_DURATION);
    digitalWrite(2, LOW);
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
    relays_number = values[4];
    //quels relais avec appareils branchés
    setDelay(values[5]);
  }
  //Que faire en temps réel ? 
}
