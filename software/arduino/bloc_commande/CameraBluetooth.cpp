#include "CameraBluetooth.h"


// fonction de création du datagramme envoyé à une caméra focus stacking en fonction d'une liste de valeurs reçues depuis le téléphone
String CameraBluetooth::createDatagramme(int* values){
  String data="";

  
  // mode programmé
  if (values[MODE] == 0)
  {
    // 0 , temps de pause entre les photos , nombre de photos à prendre , pas entre photo 1 et photo 2 ,...
    
    data+="0,"; // mode normal
    if (values[FOCUS_STACKING] == 0) values[FOCUS_STACKING] = 1; // une valeur de focus stacking de 0 ne devrait pas arriver, mais si c'est le cas, elle est passée à 1 car elle correspond au nombre de photos à prendre
    
    
    data += String(values[PAUSE_ENTRE_CAMERAS])+","; // temps de pause entre les photos
    data += String(values[FOCUS_STACKING]); // nombre de photos à prendre

    // nombre de pas entre chaque photos
    if (values[FOCUS_STACKING] > 1){
      for (int i=0; i<values[FOCUS_STACKING]-1; i++){
        data+= "," + String(params[i]);
      }
    }
    data += "," + String(-somme_des_pas); // retour à 0 à la fin de la séquence
  }

  
  // mode magneto
  else if (values[MODE] == 5){
    // 1 , direction, nombre de pas
    data += "1,"; // mode magneto
    data += String(values[DIRECTION])+",";
    data += String(values[NOMBRE_DE_PAS_TABLE] * values[NOMBRE_DE_TOUR]);
  }

  // confirmation des paramétrages, remise à zéro du focus
  else if (values[MODE] == 8){
    // 1 , direction, nombre de pas
    data += "1,"; // mode magneto
    data += String(1)+",";
    data += String(somme_des_pas);
  }
  return data;
}

void CameraBluetooth::setParams(int* params){
  // donne ses paramètres de nombre de pas à la caméra, et la somme des pas à faire
  somme_des_pas = 0;
  for (int i=0; i<8; i++){
    this->params[i] = params[i];
    somme_des_pas+=params[i];
  }
  
}
