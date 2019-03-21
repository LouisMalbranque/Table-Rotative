#include "bluetooth.h"

Bluetooth::Bluetooth(){
  
}

void Bluetooth::begin(){
  hc05.begin(9600);
}

boolean Bluetooth::receive(){
  if (!hc05.available()) return false;
   while (hc05.available()) {
    if (hc05.available() > 0) {
      char c = hc05.read();  //gets one byte from serial buffer

      data += c; //makes the string readString
    }
  }
  hc05.flush();
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
  hc05.println(data);
}

void Bluetooth::reset(){
  for(int i=0;i<8;i++){
    values[i]=0;
  }
}
