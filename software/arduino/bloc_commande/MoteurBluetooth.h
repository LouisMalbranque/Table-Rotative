#pragma once
#include "arduino.h"
#include "PeripheriqueBluetooth.h"
#include "constantes.h"

class MoteurBluetooth : public PeripheriqueBluetooth
{
public:
  using PeripheriqueBluetooth::PeripheriqueBluetooth;  
  String createDatagramme(int* values);
};
