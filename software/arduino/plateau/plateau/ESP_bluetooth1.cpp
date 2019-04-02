#include "ESP_bluetooth1.h"

ESP_bluetooth::ESP_bluetooth() {

}

void ESP_bluetooth::begin() {
  BLEDevice::init("Init");
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pcharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );
  pcharacteristic->setValue("Attente");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

void ESP_bluetooth::read() {
  data = pcharacteristic->getValue().c_str();
}
String ESP_bluetooth::getData() {
  return data;
}

void ESP_bluetooth::writeData(String s) {
      pcharacteristic->setValue(s.c_str());
}

void ESP_bluetooth::decode(){
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

int ESP_bluetooth::getValue(int i){
  return values[i];
}
