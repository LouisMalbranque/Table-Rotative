<<<<<<< HEAD:software/arduino/bloc_commande/bluetooth.h
#include "arduino.h"
#include "constantes.h"

#ifdef HC05
#include <SoftwareSerial.h>
#else
#include "BluetoothSerial.h"
#endif


#define ACCELERATION 0
#define SPEED 1
#define FRAME 2
#define STEP 3
#define DEGRES 4
#define PAUSE 5


class Bluetooth
{
  private:
    #ifdef HC05
    SoftwareSerial bt = *(new SoftwareSerial(A2,A3));
    #else
    BluetoothSerial bt;
    #endif
    String data;
    int values[MAXIMUM_NUMBER_OF_VALUES];
  public:
    Bluetooth();
    boolean receive();
    void begin();
    int getDataLength();
    int* decode();
    int getValue(int i);
    int* getValues();
    void print(String data);
    boolean isFull();
    void resetValues();
    String getData();
};
=======
#include "arduino.h"
#include "constantes.h"

#ifdef HC05
#include <SoftwareSerial.h>
#else
#include "BluetoothSerial.h"
#endif


#define ACCELERATION 0
#define SPEED 1
#define FRAME 2
#define STEP 3
#define DEGRES 4
#define PAUSE 5


class Bluetooth
{
  private:
    #ifdef HC05
    SoftwareSerial bt = *(new SoftwareSerial(A2,A3));
    #else
    BluetoothSerial bt;
    #endif
    String data;
    int values[MAXIMUM_NUMBER_OF_VALUES];
  public:
    Bluetooth();
    boolean receive();
    void begin();
    int getDataLength();
    void decode();
    int getValue(int i);
    int* getValues();
    void print(String data);
    boolean isFull();
    void resetValues();
};
>>>>>>> master:software/arduino/bloc_commande/bloc_commande/bluetooth.h
