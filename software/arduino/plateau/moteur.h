#include "arduino.h"
#include <AccelStepper.h>

class Motor
{
  private:
    AccelStepper stepper = *(new AccelStepper(1, 3, 4)); // Definition de mon objet stepper (pin step = 3; pin DIrection = 4);
  public:
    Motor();
    void begin();
    void rotate(int steps);
    void setParams(int speed, int acceleration, int direction);
    boolean isRotating();
    void run();
    int getCurrentPosition();
    void setZero();
};