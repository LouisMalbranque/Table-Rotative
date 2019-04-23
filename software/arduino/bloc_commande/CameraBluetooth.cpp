#include "CameraBluetooth.h"

String CameraBluetooth::createDatagramme(int* values){
  String data="";
  // mode programmé
  if (values[MODE] == 0)
  {
    data+="0,"; // mode normal
    if (values[FOCUS_STACKING] == 0) values[FOCUS_STACKING] = 1;
    data += String(values[PAUSE_ENTRE_CAMERAS])+",";
    data += String(values[FOCUS_STACKING]);
    
    int somme_de_pas = 0;
    if (values[FOCUS_STACKING] > 1){
      for (int i=0; i<values[FOCUS_STACKING]-1; i++){
        data+= "," + String(params[i]);
        somme_de_pas += params[i];
      }
    }
    data += "," + String(-somme_de_pas);
  }

  
  // mode magneto
  else if (values[MODE] == 5){
    data += "1,"; // mode magneto
    data += String(values[DIRECTION])+",";
    data += String(values[NOMBRE_DE_PAS_TABLE] * values[NOMBRE_DE_TOUR]);
  }
  return data;
}

void CameraBluetooth::setParams(int* params){
  for (int i=0; i<8; i++){
    this->params[i] = params[i];
  }
}
