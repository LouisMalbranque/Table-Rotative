#include "MoteurBluetooth.h"


// crée le datagramme à envoyer au moteur en fonction des valeurs reçues
String MoteurBluetooth::createDatagramme(int* values)
{
  String datagramme = "";
  int steps;
  
  // le datagramme dépend du mode de fonctionnement
  switch(values[MODE]){


    case 0: // rotation programmée, 1 tour divisé en n parties
      steps = (int) (values[NOMBRE_DE_PAS_TABLE] / values[NOMBRE_DE_PHOTOS]);
      datagramme =  String(values[ACCELERATION]) + "," + String(values[VITESSE]) + "," + String(values[DIRECTION]) + ",0," + String(steps); 
      break;

    

    case 1: // rotation temps réel, 2 cas possible, en temps ou en tour

      datagramme = String(values[ACCELERATION]) + "," + String(values[VITESSE]) + "," + String(values[DIRECTION]) + "," + String(values[CHOIX_ROTATION]) + ",";
      
      switch(values[CHOIX_ROTATION]){

        case 0: // en nombre de pas
          datagramme += String(values[NOMBRE_DE_TOUR] * values[NOMBRE_DE_PAS_TABLE]);
          break;
        

        case 1: // en temps
          datagramme += String(values[TEMPS_DE_ROTATION] * 1000);
          break;
        

        default:
          Serial.println("Choix de rotation invalide");
          return "";
      }
      break;    

         
    default:
      Serial.println("Mode invalide pour la création du datagramme moteur");
      return "";
      break; 
  }

  
  return datagramme;
}
