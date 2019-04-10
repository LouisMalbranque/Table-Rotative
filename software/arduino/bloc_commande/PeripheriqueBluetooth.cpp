#include "PeripheriqueBluetooth.h"


PeripheriqueBluetooth::PeripheriqueBluetooth()
{
}

PeripheriqueBluetooth::PeripheriqueBluetooth(const char* serviceUUID, const char* charUUID)
{
   this->serviceUUID = *(new BLEUUID(serviceUUID));
   this->charUUID = *(new BLEUUID(charUUID));
}


PeripheriqueBluetooth::~PeripheriqueBluetooth()
{
}

void PeripheriqueBluetooth::write(String data)
{
  characteristics->writeValue(data.c_str(), data.length());
}

String PeripheriqueBluetooth::read()
{
  return characteristics->readValue().c_str(); 
}

void PeripheriqueBluetooth::begin()
{
}

String PeripheriqueBluetooth::createDatagramme(int* values){
  return "";
}

void PeripheriqueBluetooth::setCharacteristics(BLERemoteCharacteristic* characteristics){
  this->characteristics = characteristics;
}
BLEUUID PeripheriqueBluetooth::getServiceUUID(){
  return serviceUUID ;
}
BLEUUID PeripheriqueBluetooth::getCharUUID(){
  return charUUID ;
}
