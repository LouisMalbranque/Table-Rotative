#include "arduino.h"
#include "constantes.h"



class Relays
{
  private:
    unsigned int pinRelay[9] = {CAMERA1,CAMERA2,CAMERA3,CAMERA4,CAMERA5,CAMERA6,CAMERA7,CAMERA8,CAMERA9};
    int delayBetweenTriggersMs = 0;
     int values[MAXIMUM_NUMBER_OF_VALUES];
     int relays_number=9;
  public:
    Relays();
    void begin();
    void triggerAll();
    void triggerSimultaneous();
    void setDelay(int totalDelay);
    void setValues(int *values);
};
 
