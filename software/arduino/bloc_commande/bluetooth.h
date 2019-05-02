#include "arduino.h"
#include "constantes.h"

#include "BluetoothSerial.h"

/*

#define ACCELERATION 0
#define SPEED 1
#define FRAME 2
#define STEP 3
#define DEGRES 4
#define PAUSE 5

*/

/*

classe de gestion de la communication bluetooth avec le téléphone

*/

class Bluetooth
{
  private:
    BluetoothSerial bt;
    String data;
    int values[MAXIMUM_NUMBER_OF_VALUES];
  public:
    Bluetooth();
    boolean receive();          // reception des données, renvoie true si une data était dispoblible et a été reçue
    void begin();               // création des objets
    int getDataLength();        // renvoie la longueur de la chaine reçue
    int* decode();              // décode le message reçu (string) en tableau d'int et renvoie le tableau
    int getValue(int i);        // renvoie la valeur à la position i dans le tableau décodé
    int* getValues();           // renvoie le tableau d'int décodé
    void print(String data);    // écrit sur le téléphone
    String getData();           // renvoie la data reçue
};
