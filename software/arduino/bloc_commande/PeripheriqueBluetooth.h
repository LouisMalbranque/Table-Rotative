#pragma once
#include "arduino.h"
#include "Peripherique.h"
#include "BLEDevice.h"
#include "BLEUUID.h"

class PeripheriqueBluetooth: public Peripherique
{
private:
	BLEUUID serviceUUID; // UUID de service
  BLEUUID charUUID; // UUID de charactéristique
public:
  BLERemoteCharacteristic *characteristics;
  bool connected;

  PeripheriqueBluetooth(); // constructeur par défaut
	PeripheriqueBluetooth(const char* serviceUUID, const char* charUUID); // conctructeur qui donne ses UUID au périphérique
	~PeripheriqueBluetooth(); // destructeur par défaut

  void write(String data); // écrit dans les charactéristiques du périphérique
  String read(); // lis depuis les charactéristiques du préiphérque
	String createDatagramme(int* values); // crée le datagramme à partir des valeurs reçues (renvoie un string vide par défaut)



  void setCharacteristics(BLERemoteCharacteristic *characteristics); // donnes ses charactéristiques
  BLEUUID getServiceUUID(); // renvoie l'UUID de service
  BLEUUID getCharUUID(); // renvoie l'UUID de charactéristiques

};
