#include "bluetooth.h"

Bluetooth::Bluetooth(){
  
}

void Bluetooth::begin(){
    #ifdef HC05
    bt.begin(9600);
    #else
    bt.begin("Boitier de commande");
    #endif
}

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
int Bluetooth::getDataLength(){
  return (int)(data.length());
}

void Bluetooth::decode(){
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
}

int* Bluetooth::getValues(){
  return values;
}

int Bluetooth::getValue(int i){
  return values[i];
}

void Bluetooth::print(String data){
  bt.println(data);
}

boolean Bluetooth::isFull(){
  for (int i=0;i<MAXIMUM_NUMBER_OF_VALUES;i++){
    if (values[i]!=0) return true;
  }
  return false;
}

void Bluetooth::resetValues(){
  for (int i=0;i<MAXIMUM_NUMBER_OF_VALUES;i++){
    values[i]=0;
  }
}
