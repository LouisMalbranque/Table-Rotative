#include "arduino.h"
#include "constantes.h"

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI


class Nrf
{
  private:
    int data[NRF_DATA_LENGTH];
  public:
    Nrf();
    void begin();
    void send(int data[NRF_DATA_LENGTH]);
    void receive();
    int getValue(int i);
    void clear();
};
