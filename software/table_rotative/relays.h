#include "arduino.h"

#define PULSE_DURATION 1500
#define RELAYS_NUMBER 3

class Relays
{
  private:
    unsigned int pinRelay[9] = {4,5,6,7,8,9,10,11,12};
    int delayBetweenTriggersMs = 0;
  public:
    Relays();
    void begin();
    void triggerAll();
    void triggerSimultaneous();
    void setDelay(int totalDelay);
};
/*
relayEnCours = 0;

trigger{
  if (millis() > 1000){
   relayEnCours ++; 
  }
  digitalWrite( 00 );
}*/
 
