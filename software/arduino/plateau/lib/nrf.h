#ifdef NRF
#include "arduino.h"
#include <SPI.h>      // Pour la communication via le port SPI
#include <Mirf.h>     // Pour la gestion de la communication
#include <nRF24L01.h> // Pour les définitions des registres du nRF24L01
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI

#define DATA_LENGTH 5

#define ACCELERATION 0
#define SPEED 1
#define DIRECTION 2
#define STEPS 3
#define TIME 4




class Nrf
{
  private:
    int data[DATA_LENGTH];
  public:
    Nrf();
    void begin();
    void send(int data[1]);
    void receive();
    int getValue(int i);
    boolean isEmpty();
    void printData();
    void clear();
};
#endif
