#include "arduino.h"
#include <AccelStepper.h>

#define STEPS 3600

class Motor
{
  private:
    AccelStepper stepper = new AccelStepper(1, 3, 4); // Definition de mon objet stepper (pin step = 3; pin DIrection = 4);
  public:
    Motor();
    void begin();
    void rotate(int steps);
    void setParams(int speed, int acceleration);
    boolean isRotating();
    void run();
};
