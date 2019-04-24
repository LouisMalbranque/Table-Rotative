#include "arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "constantes.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class ESP_server{
  private:
    String data;
    int values[MAXIMUM_NUMBER_OF_VALUES];
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
