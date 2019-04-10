#include "nrf.h"



Nrf::Nrf(){
  
}
void Nrf::begin(){
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothéque

  Mirf.channel = 1; // Choix du cannal de communication (12DATA_LENGTH canaux disponible, de 0 à 127)
  Mirf.payload = sizeof(int) * DATA_LENGTH; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception

  for (int i=0; i<DATA_LENGTH; i++) data[i]=0;
}

void Nrf::send(int data[DATA_LENGTH]){
  Mirf.send((byte *) data);
  // On attend la fin de l'envoi
  while (Mirf.isSending());
  delay(20);
}

void Nrf::receive(){
   if (Mirf.dataReady()) {
      Mirf.getData((byte *) &data);
   }
}

int Nrf::getValue(int i){
  return data[i];
}

boolean Nrf::isEmpty(){
  for (int i=0; i<DATA_LENGTH; i++){
    if (data[i] != 0) return false;
  }
  return true;
}

void Nrf::printData(){
  for (int i=0; i<DATA_LENGTH; i++){
    Serial.print(data[i]);
    Serial.print("\t");
  }  
  Serial.println();
}

void Nrf::clear(){
  for (int i=0; i<DATA_LENGTH; i++){
    data[i]=0;
  }  
}
