#include "PeripheriqueBluetooth.h"

// constructeur par défaut
PeripheriqueBluetooth::PeripheriqueBluetooth()
{
}
// constructeur qui donne les UUID de service et de charachéristiques
PeripheriqueBluetooth::PeripheriqueBluetooth(const char* serviceUUID, const char* charUUID)
{
   this->serviceUUID = *(new BLEUUID(serviceUUID));
   this->charUUID = *(new BLEUUID(charUUID));
}
// destructeur par défaut
PeripheriqueBluetooth::~PeripheriqueBluetooth()
{
}
// écrit dans le string d'échange
void PeripheriqueBluetooth::write(String data)
{
  characteristics->writeValue(data.c_str(), data.length());
}
// lis les charactéristiques pour récupérer le string d'échange
String PeripheriqueBluetooth::read()
{
  return characteristics->readValue().c_str(); 
}
// crée un datagramme vide par défaut
String PeripheriqueBluetooth::createDatagramme(int* values){
  return "";
}
// donne ses charactéristiques 
void PeripheriqueBluetooth::setCharacteristics(BLERemoteCharacteristic* characteristics){
  this->characteristics = characteristics;
}
// renvoie l'UUID de service
BLEUUID PeripheriqueBluetooth::getServiceUUID(){
  return serviceUUID ;
}
// renvoie l'UUID de charactéristiques
BLEUUID PeripheriqueBluetooth::getCharUUID(){
  return charUUID ;
}
