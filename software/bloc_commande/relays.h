#include "arduino.h"
#include "constantes.h"



class Relays
{
  private:
    unsigned int pinRelay[9] = {4,5,6,7,8,9,10,11,12};
    int delayBetweenTriggersMs = 0;
     int values[MAXIMUM_NUMBER_OF_VALUES];
     int relays_number=0;
  public:
    Relays();
    void begin();
    void triggerAll();
    void triggerSimultaneous();
    void setDelay(int totalDelay);
    void setValues(int *values);
};
 
