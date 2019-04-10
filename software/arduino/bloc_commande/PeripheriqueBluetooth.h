#pragma once
#include "arduino.h"
#include "Peripherique.h"
#include "BLEDevice.h"
#include "BLEUUID.h"

class PeripheriqueBluetooth: public Peripherique
{
private:
	BLEUUID serviceUUID;
  BLEUUID charUUID;
public:
  BLERemoteCharacteristic *characteristics;
  bool connected;
  PeripheriqueBluetooth();
	PeripheriqueBluetooth(const char* serviceUUID, const char* charUUID);
	~PeripheriqueBluetooth();

	void begin(); 
  void write(String data);
  String read();  
	String createDatagramme(int* values);



  void setCharacteristics(BLERemoteCharacteristic *characteristics);
  String getData();
  BLEUUID getServiceUUID();
  BLEUUID getCharUUID();

};
