#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI


int data[8];

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Mirf.cePin = 9; // Broche CE sur D9
  Mirf.csnPin = 10; // Broche CSN sur D10
  Mirf.spi = &MirfHardwareSpi; // On veut utiliser le port SPI hardware
  Mirf.init(); // Initialise la bibliothéque

  Mirf.channel = 1; // Choix du cannal de communication (128 canaux disponible, de 0 à 127)
  Mirf.payload = sizeof(int) * 8; // Taille d'un message (maximum 32 octets)
  Mirf.config(); // Sauvegarde la configuration dans le module radio

  Mirf.setTADDR((byte *) "nrf02"); // Adresse de transmission
  Mirf.setRADDR((byte *) "nrf01"); // Adresse de réception

  Serial.println("Listening");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Mirf.dataReady()) {
      Mirf.getData((byte *) &data);
      for (int i=0; i<8; i++){
        Serial.print(data[i]);
        Serial.print("\t");
      }
      Serial.println();
   }   
}
