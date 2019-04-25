#include "ESP_server.h"

class DisconnectCallbacks: public BLEServerCallbacks{
  public:
    void onConnect(BLEServer* pServer);
    void onConnect(BLEServer* pServer, esp_ble_gatts_cb_param_t *param);
    void onDisconnect(BLEServer* pServer);
};

void DisconnectCallbacks::onConnect(BLEServer* pServer) { digitalWrite(LED,HIGH); }
void DisconnectCallbacks::onConnect(BLEServer* pServer, esp_ble_gatts_cb_param_t *param) {}
void DisconnectCallbacks::onDisconnect(BLEServer* pServer) { ESP.restart(); }

ESP_server::ESP_server() {

}

void ESP_server::begin() {
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
  BLEDevice::init("Init");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pcharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pService->start();
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  pServer->setCallbacks(new DisconnectCallbacks());
  
}

String ESP_server::read() {
   data = pcharacteristic->getValue().c_str();
   return data;
}

void ESP_server::decode(){
  char* valuesent;
  int i=0;
  if (data != "0") {
    i = 0;
    char buf[data.length() + 1];
    data.toCharArray(buf, data.length() + 1);
    valuesent = strtok(buf, ",");
    while (valuesent != NULL) {
      values[i] = atoi(valuesent);
      i++;
      valuesent = strtok(NULL, ",");
    }
    data = "";
  }
}

void ESP_server::writeData(String s) {
      pcharacteristic->setValue(s.c_str());
}

String ESP_server::getData() {
  return data;
}

int ESP_server::getValue(int i){
  return values[i];
}
