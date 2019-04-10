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

class ESP_bluetooth{
  private:
    BLEScan* pBLEScan;
    

    BLEScanResults scanResults;
    
  public:
  ESP_bluetooth();
  void begin();
  boolean connect(PeripheriqueBluetooth *periph);
  void scan();
};
