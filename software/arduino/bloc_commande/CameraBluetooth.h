#include "arduino.h"
#include "PeripheriqueBluetooth.h"
#include "constantes.h"
class CameraBluetooth: public PeripheriqueBluetooth
{
  public:
    int params[9];
    int somme_des_pas = 0;

    using PeripheriqueBluetooth::PeripheriqueBluetooth;

    String createDatagramme(int* values);
    void setParams(int* params);
};
