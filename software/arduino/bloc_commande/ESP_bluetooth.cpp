#include "ESP_bluetooth.h"


static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    Serial.println((char*)pData);
}

void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

  } // onResult

ESP_bluetooth::ESP_bluetooth(){
  
}

void ESP_bluetooth::begin(){
  
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
  BLEDevice::init("");
  
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  
}


void ESP_bluetooth::scan(){
    Serial.println("Starting scan");
    scanResults = pBLEScan->start(5, false);
    Serial.println("Scan finished");
    
}


boolean ESP_bluetooth::connect(PeripheriqueBluetooth *periph){
  pClient  = BLEDevice::createClient();
  
  
  Serial.print("scan Count");
  Serial.println(scanResults.getCount());
  Serial.print("Starting new connection to ");
  Serial.println(periph->getServiceUUID().toString().c_str());
  for (int i=0; i<scanResults.getCount(); i++){
    
    BLEAdvertisedDevice advertisedDevice = scanResults.getDevice(i);
    Serial.print("haveServiceUUID ");
    Serial.println(advertisedDevice.haveServiceUUID());

    Serial.print("isAdvertisingService ");
    Serial.println(advertisedDevice.isAdvertisingService(periph->getServiceUUID()));
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(periph->getServiceUUID())){
      
        BLEAddress *pServerAddress;
        pServerAddress = new BLEAddress(advertisedDevice.getAddress());
        
        Serial.println("before connect");
        pClient->disconnect();
        pClient->connect(*pServerAddress);// if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
        delay(1000);
        Serial.println(" - Connected to server");
    
        // Obtain a reference to the service we are after in the remote BLE server.
        BLERemoteService* pRemoteService = pClient->getService(advertisedDevice.getServiceUUID());
        if (pRemoteService == NULL) {
          Serial.print("Failed to find our service UUID: ");
          Serial.println(periph->getServiceUUID().toString().c_str());
          pClient->disconnect();
          return false;
        }
        Serial.println(" - Found our service");
    
     
        // Obtain a reference to the characteristic in the service of the remote BLE server.
        BLERemoteCharacteristic* characteristics = pRemoteService->getCharacteristic(periph->getCharUUID());
        if (characteristics == NULL) {
          Serial.print("Failed to find our characteristic UUID: ");
          Serial.println(periph->getCharUUID().toString().c_str());
          pClient->disconnect();
          return false;
        }
        Serial.println(" - Found our characteristic");
    
        // Read the value of the characteristic.
        if(characteristics->canRead()) {
          std::string value = characteristics->readValue();
          Serial.print("The characteristic value was: ");
          Serial.println(value.c_str());
        }
    
        if(characteristics->canNotify())
          characteristics->registerForNotify(notifyCallback);

        periph->setCharacteristics(characteristics); 
        periph->connected = true;
        return true;
    }
  }
  return false;  
}
