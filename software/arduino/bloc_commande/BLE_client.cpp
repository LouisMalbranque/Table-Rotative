#include "BLE_client.h"

// callback qui écrit les propriétés d'un périqphérique BLE quand il est notifié
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

// callback qui écrit les propriété d'un service détecté
void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

  } // onResult

BLE_client::BLE_client(){
  // constructeur par défaut
}

// initie le client BLE
void BLE_client::begin(){  
  BLEDevice::init("BLE Boitier");
  
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  
}


// scan les service BLE disponibles pendant 5 secondes
void BLE_client::scan(){
    Serial.println("Starting scan");
    scanResults = pBLEScan->start(5, false);
    Serial.println("Scan finished");
}

// connecte le client ) un périphérique bluetooth periph donné par référence
boolean BLE_client::connect(PeripheriqueBluetooth *periph){
  pClient  = BLEDevice::createClient();
  
  Serial.print("Starting new connection to ");
  Serial.println(periph->getServiceUUID().toString().c_str());
  for (int i=0; i<scanResults.getCount(); i++){
    
    BLEAdvertisedDevice advertisedDevice = scanResults.getDevice(i); // parcourt la liste des périphériques détectés

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(periph->getServiceUUID())){
        // si le bon périphérique est trouvé, on s'y connecte
        BLEAddress *pServerAddress;
        pServerAddress = new BLEAddress(advertisedDevice.getAddress());
        
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

        // donne au périphérique les characteristiques
        periph->setCharacteristics(characteristics); 
        periph->connected = true;
        return true;
    }
  }
  return false;  
}
