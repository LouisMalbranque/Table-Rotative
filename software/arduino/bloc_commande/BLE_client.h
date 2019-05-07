#include "arduino.h"
#include "constantes.h"
#include "BLEDevice.h"
#include "PeripheriqueBluetooth.h"


#define MAX_NUMBER_BLUETOOTH_SCAN 15

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic, 
  uint8_t* pData,
  size_t length,
  bool isNotify);

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice);
}; 


class BLE_client{
  private:
    BLEScan* pBLEScan;  // scanner ble
    BLEScanResults scanResults; // resultats du scan
    BLEClient* pClient; // client ble
  public:
  BLE_client(); // constructeur ble
  void begin(); // initialisation du client ble
  boolean connect(PeripheriqueBluetooth *periph); // connecte au périphérique donné par référence
  void scan(); // scan les périphériques ble environant
};
