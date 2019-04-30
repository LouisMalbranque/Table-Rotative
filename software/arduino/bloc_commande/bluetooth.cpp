#include "bluetooth.h"

/* librairie de gestion du bluetooth avec le téléphone

  gere l'écriture et la lecture depuis le bluetooth du téléphone, et le décodage des messages reçus

*/


Bluetooth::Bluetooth(){
  
}


// initialisation du bluetooth
void Bluetooth::begin(){
    bt.begin("Boitier de commande");
}


// fonction de réception des données, elles sont stoquées dans le string data*
// renvoie true si une information a été reçue, false sinon
boolean Bluetooth::receive(){

  if (bt.available() == 0) return false;
   while (bt.available()) {
    if (bt.available() > 0) {
      char c = bt.read();  //gets one byte from serial buffer
      data += c; //makes the string readString
    }
  }
  bt.flush();
  return true;

}

// récupère la longueur du message
int Bluetooth::getDataLength(){
  return (int)(data.length());
}


// décode le message stocké dans data
// retourne un tableau d'entier contenant toutes les informations séparées par des virgules
int* Bluetooth::decode(){
  char* valuesent;
  int i=0;
  if (data != "") {
    i = 0;
    char buf[data.length() + 1];
    data.toCharArray(buf, data.length() + 1);
    valuesent = strtok(buf, ",");
    while (valuesent != NULL) {
      values[i] = atoi(valuesent);
      i++;
      valuesent = strtok(NULL, ",");
    }
    data = "";
  }
  return values;
}

// renvoie les valeures décodées
int* Bluetooth::getValues(){
  return values;
}

// renvoie la valeur décodée à l'indice i
int Bluetooth::getValue(int i){
  return values[i];
}

// écrit dans le port série du téléphone
void Bluetooth::print(String data){
  data+=",";
  delay(50);
  bt.println(data);
  delay(50);
  Serial.println("au telephone: "+data);

}

// renvoie la chaine de caractère reçue (mais pas décodée)
String Bluetooth::getData(){
  return data;
}
