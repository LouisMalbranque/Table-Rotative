#include "MoteurBluetooth.h"

String MoteurBluetooth::createDatagramme(int* values)
{
  String datagramme = "";
  int steps;
  
  switch(values[MODE]){
    case 0:
      steps = (int) (values[STEPS] / values[FRAME]);
      datagramme =  String(values[ACCELERATION]) + "," + String(values[SPEED]) + "," + String(values[DIRECTION]) + "," + steps + "," + String(values[ROTATION_TIME]); 
      break;
    case 1:
      steps = values[STEPS]*values[ROTATION_NUMBER];
      datagramme = String(values[ACCELERATION]) + "," + String(values[SPEED]) + "," + String(values[DIRECTION]) + "," + steps + "," + String(values[ROTATION_TIME]); 
      break;       
    default:
      break; 
  }
  return datagramme;
}
