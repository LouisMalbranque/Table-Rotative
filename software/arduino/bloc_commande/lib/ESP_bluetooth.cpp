#include "ESP_bluetooth.h"

static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");

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

void MyClientCallback::onConnect(BLEClient* pclient) {
}

void MyClientCallback::onDisconnect(BLEClient* pclient) {
  //pclient.setConnected(false);
  Serial.println("onDisconnect");
}

void MyAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      BLEAdvertisedDevice myDevice = *(new BLEAdvertisedDevice(advertisedDevice));
      //advertisedDevice.setDoConnect(true);
      //advertisedDevice.setDoScan(true);

    } // Found our server
  } // onResult


ESP_bluetooth::ESP_bluetooth(){
  
}

void ESP_bluetooth::begin(){
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
  //bluetooth.begin();
   
   Serial.println("Bluetooth Device is ready to pair");
}


boolean ESP_bluetooth::connect(BLEUUID serviceUUID){
    this->serviceUUID = serviceUUID;
    
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");


    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);

    connected = true;
    return true;
}

boolean ESP_bluetooth::read(){
  data=pRemoteCharacteristic->readValue().c_str();
  if (data != "") return true;
  return false; 
}
void ESP_bluetooth::write(String data){
  pRemoteCharacteristic->writeValue(data.c_str(), data.length());
}
void ESP_bluetooth::scan(){
  BLEDevice::getScan()->start(0);
}
void ESP_bluetooth::setConnected(boolean connected){
  this->connected = connected;
}
void ESP_bluetooth::setDoScan(boolean doScan){
  this->doScan = doScan;
}
void ESP_bluetooth::setDoConnect(boolean doConnect){
  this->doConnect = doConnect;
}
String ESP_bluetooth::getData(){
  return data;
}
