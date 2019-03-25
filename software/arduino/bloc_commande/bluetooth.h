#include "arduino.h"
#include <SoftwareSerial.h>
#include "constantes.h"

#define ACCELERATION 0
#define SPEED 1
#define FRAME 2
#define STEP 3
#define DEGRES 4
#define PAUSE 5


class Bluetooth
{
  private:
    SoftwareSerial hc05 = *(new SoftwareSerial(A2,A3));
    String data;
    int values[MAXIMUM_NUMBER_OF_VALUES];
  public:
    Bluetooth();
    void receive();
    void begin();
    int getDataLength();
    void decode();
    int getValue(int i);
    int* getValues();
    void print(String data);
    boolean isFull();
    void resetValues();
};