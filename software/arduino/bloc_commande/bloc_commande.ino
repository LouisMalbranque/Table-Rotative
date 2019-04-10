#include "ESP_bluetooth.h"
#include "MoteurBluetooth.h"
#include "bluetooth.h"
#include "Instruction.h"
#include "QueueList.h"
#include "CameraThread.h"


MoteurBluetooth moteur("4fafc201-1fb5-459e-8fcc-c5c9c331914b", "beb5483e-36e1-4688-b7f5-ea07361b26a8");
CameraThread camera;


ESP_bluetooth esp;
Bluetooth telephone;

QueueList<Instruction> instructions;
Instruction instructionEnCours;

int* values;
void setup() {
  Serial.begin(115200);
  
  telephone.begin();
  
  esp.begin();
  esp.scan();

  
  esp.connect(&moteur);

  camera.begin();

}

void loop() {
    delay(100);


  
    if (telephone.receive()){
      Serial.print("Data received : ");
      Serial.print(telephone.getData());
      values = telephone.decode();

      switch(values[MODE]){
        case 0: // mode programmé
          Serial.println(" Mode programmé");
          for (int i=0; i<values[FRAME]; i++){
             Instruction newInstr = {&moteur, moteur.createDatagramme(values)};
             instructions.push(newInstr);
             Instruction newInstr2 = {&camera, camera.createDatagramme(values)};
             instructions.push(newInstr2);
          }
          break;

          
        case 1: // mode temps reel
          Serial.println(" Mode temps réel");
          Instruction newInstr = {&moteur, moteur.createDatagramme(values)};
          instructions.push(newInstr);
          break;
          
      }
    }

    if (!instructions.isEmpty()){
      instructionEnCours = instructions.peek();
      if (instructionEnCours.target->read() == "0"){
        Serial.print("Sending datagramme : ");
        Serial.println(instructionEnCours.data);
        instructionEnCours.target->write(instructionEnCours.data);
      }

      if (instructionEnCours.target->read() == "1"){
      }

      if (instructionEnCours.target->read() == "2"){
        Serial.println("Instruction finished");
        instructionEnCours.target->write("0");
        instructions.pop();
        delay(10);
      }
    }
    
}
