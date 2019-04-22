#include "arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "constantes.h"

#define SERVICE_UUID        "1540c1dc-b7a8-484d-bfb6-6c5897339ab3"
#define CHARACTERISTIC_UUID "54b2a4c4-c9ce-41bb-9441-705981242337"



class ESP_server{
  private:
    String data;
    int values[11];
    BLEServer *pServer;
    BLEService *pService;
    BLEAdvertising *pAdvertising;
    BLECharacteristic *pcharacteristic;
  public:
    ESP_server();
    void begin();
    String read();
    String getData();
    int getValue(int i);
    void writeData(String s);
    void decode();
};
