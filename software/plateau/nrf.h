#include "arduino.h"

#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define TYPE 0
#define PROGRAMMED 0

class Nrf
{
  private:
    int data[8];
  public:
    Nrf();
    void begin();
    void send(int data[8]);
    void receive();
    int getValue(int i);
    boolean isEmpty();
};
