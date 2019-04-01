#include "arduino.h"
#include "constantes.h"

class ESP_bluetooth{
  private:
  BLEServer *pServer;
  BLEService *pService;
  BLECharacteristic *pcharacteristic;
  BLEAdvertising *pAdvertising
  
  public:
  ESP_bluetooth();
  void begin();
}

