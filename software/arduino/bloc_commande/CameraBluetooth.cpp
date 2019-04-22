#include "CameraBluetooth.h"

String CameraBluetooth::createDatagramme(int* values){
  String data="";
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
  return data;
}

void CameraBluetooth::setParams(int* values){
  for (int i=0; i<9; i++){
    this->params[i] = values[i+3];
  }
}
