#include "appareil.h"

// classe de controle de l'appareil photo

// constructeur par défaut
Appareil::Appareil(){
  
}
// assignation de la pin de commande de l'appareil
void Appareil::begin( int pin ){
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

// fonction de prise de photo, la pin de commande est gardée au niveau haut pendant le temps_activation (ms)
void Appareil::prendrePhoto( int temps_activation ){
  digitalWrite(pin, HIGH);
  delay(temps_activation);
  digitalWrite(pin, LOW);
}
