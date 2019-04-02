#include "nrf.h"
#include "constantes.h"

Nrf::Nrf(){
  
}
void Nrf::begin(){
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothéque

  Mirf.channel = 1; // Choix du cannal de communication (128 canaux disponible, de 0 à 127)
  Mirf.payload = sizeof(int) * NRF_DATA_LENGTH; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf01"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf02"); // Adresse de réception
}

void Nrf::send(int data[NRF_DATA_LENGTH]){
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
  int r = data[i];
  data[i] = 0;
  return r;
}

void Nrf::clear(){
  for (int i=0;i<NRF_DATA_LENGTH;i++){
    data[i]=0;
  }
}
