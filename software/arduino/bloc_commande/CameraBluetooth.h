#include "arduino.h"
#include "PeripheriqueBluetooth.h"
#include "constantes.h"

// la classe caméra bluetooth hérite de périphérique bluetoorh, elle profite donc de 
class CameraBluetooth: public PeripheriqueBluetooth
{
  public:
    int params[9];
    int somme_des_pas = 0;

    // permet d'utiliser les constructieurs de la classe mère
    using PeripheriqueBluetooth::PeripheriqueBluetooth;

    String createDatagramme(int* values); // fonction de création du datagramme à envoyer
    void setParams(int* params); // fonction de paramétrage du focus stacking
};
