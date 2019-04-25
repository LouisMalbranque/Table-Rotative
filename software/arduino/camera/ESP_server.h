#include "arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "constantes.h"

#define SERVICE_UUID        "1c1e2ea0-7c18-4c35-b38d-04aa84086d66"
#define CHARACTERISTIC_UUID "238df85b-af2f-4817-841f-7ce4330ad0a8"



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
