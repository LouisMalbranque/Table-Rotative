#include "appareil.h"

Appareil::Appareil(){
  
}
void Appareil::begin( int pin ){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}
void Appareil::prendrePhoto( int temps_activation ){
  digitalWrite(pin, HIGH);
  delay(temps_activation);
  digitalWrite(pin, LOW);
}
