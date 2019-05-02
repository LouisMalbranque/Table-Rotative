#include "arduino.h"
#include "PeripheriqueBluetooth.h"
#include "constantes.h"

class MoteurBluetooth : public PeripheriqueBluetooth
{
public:
  using PeripheriqueBluetooth::PeripheriqueBluetooth;  // utilise les contructeurs de PeripheriqueBluetooth
  String createDatagramme(int* values); // crée le datagramme avec les valeurs reçues
};
