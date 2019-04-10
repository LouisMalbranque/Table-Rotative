<<<<<<< HEAD:software/arduino/bloc_commande/ESP_bluetooth.h
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
=======
#include "arduino.h"
#include "constantes.h"
#include "BLEDevice.h"



static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify);

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient);
  void onDisconnect(BLEClient* pclient);
};

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice);
}; 

class ESP_bluetooth{
  private:
    String data;

    BLERemoteCharacteristic* pRemoteCharacteristic;
    BLEUUID charUUID = *(new BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"));
    BLEUUID serviceUUID;
    
  public:
  ESP_bluetooth();
  void begin();
  boolean connect(BLEUUID serviceUUID);
  void receive();
  String read();
  void write(String data);
  void write(int* tab);
  void scan();
  String getData();
};
>>>>>>> master:software/arduino/bloc_commande/bloc_commande/ESP_bluetooth.h
