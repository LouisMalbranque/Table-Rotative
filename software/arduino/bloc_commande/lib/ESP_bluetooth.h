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
    boolean  doConnect = false ;
    boolean  connected = false ; 
    boolean  doScan = false ;
    String data;

    BLERemoteCharacteristic* pRemoteCharacteristic;
    BLEAdvertisedDevice* myDevice;
    BLEUUID charUUID = *(new BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"));
    BLEUUID serviceUUID;
    
  public:
  ESP_bluetooth();
  void begin();
  boolean connect(BLEUUID serviceUUID);
  void receive();
  boolean read();
  void write(String data);
  void scan();
  void setConnected(boolean connected);
  void setDoConnect(boolean doConnect);
  void setDoScan(boolean doScan);
  String getData();
};
