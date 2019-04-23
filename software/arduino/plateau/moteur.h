#include "arduino.h"
#include "constantes.h"
#include <AccelStepper.h>

class Motor
{
  private:
    AccelStepper stepper = *(new AccelStepper(1, PIN_STEP, PIN_DIR));
    int direction;
  public:
    Motor();
    void begin();
    void rotate(int steps);
    void setParams(int speed, int acceleration, int direction);
    boolean isRotating();
    void run();
    int getCurrentPosition();
    void setZero();
    int timeLeft();
    int distanceLeft();
    void setRotationTime(int temps_restant);
};
