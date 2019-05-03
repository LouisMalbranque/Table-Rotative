#include "arduino.h"
#include "constantes.h"
#include <AccelStepper.h>

class Motor
{
  private:
    AccelStepper stepper = *(new AccelStepper(1, PIN_STEP, PIN_DIR)); // Definition de mon objet stepper
    int direction;
  public:
    Motor();
    void begin(); // démarre le module et initialise les paramètres
    void rotate(int steps); // donne le nombre de pas à effectuer
    void setParams(int speed, int acceleration, int direction); // set l'acceleration, la vitesse et la direction
    boolean isRotating(); // renvoie vrai si le moteur n'est pas à sa position finale
    void run(); // fait tourner le moteur
    int getCurrentPosition(); // renvoie la position actuelle du moteur
    void setZero(); // remet le moteur à 0
    int timeLeft();
    int distanceLeft();
    void setRotationTime(int temps_restant);
};
