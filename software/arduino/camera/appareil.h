#include "arduino.h"

class Appareil
{
  private:
    int pin;
  public:
    Appareil();
    void begin( int pin );
    void prendrePhoto( int delay_activation );
};
