#include "arduino.h"

// classe d'activation de l'appareil photo

class Appareil
{
  private:
    int pin; // pin de controle
  public:
    Appareil();
    void begin( int pin ); // assignation des pins
    void prendrePhoto( int delay_activation ); // prise de photo pendant delay_activation (ms)
};
