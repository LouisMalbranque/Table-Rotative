#include "arduino.h"
#include <SoftwareSerial.h>

class Bluetooth
{
  private:
    SoftwareSerial hc05 = *(new SoftwareSerial(A2,A3));
    String data;
    int values[9];
  public:
    Bluetooth();
    void receive();
    void begin();
    int getDataLength();
    int* decode();
};
