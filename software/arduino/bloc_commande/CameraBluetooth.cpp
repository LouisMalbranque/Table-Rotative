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
    
    if (values[FOCUS_STACKING] > 1){
      for (int i=0; i<values[FOCUS_STACKING]-1; i++){
        data+= "," + String(params[i]);
      }
    }
    data += "," + String(-somme_des_pas);
  }

  
  // mode magneto
  else if (values[MODE] == 5){
    data += "1,"; // mode magneto
    data += String(values[DIRECTION])+",";
    data += String(values[NOMBRE_DE_PAS_TABLE] * values[NOMBRE_DE_TOUR]);
  }
  else if (values[MODE] == 8){
    data += "1,"; // mode magneto
    data += String(1)+",";
    data += String(somme_des_pas);
  }
  return data;
}

void CameraBluetooth::setParams(int* params){
  somme_des_pas = 0;
  for (int i=0; i<8; i++){
    this->params[i] = params[i];
    somme_des_pas+=params[i];
  }
  
}
