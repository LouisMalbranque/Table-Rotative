<<<<<<< HEAD:software/arduino/bloc_commande/bloc_commande.ino
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
=======
#define ESP32 1

#include "constantes.h"

#include "bluetooth.h"
#include "lcd.h"
#include "relays.h"
#include "ESP_bluetooth.h"



Bluetooth bluetooth;
Lcd lcd;
Relays relays;
ESP_bluetooth esp_bluetooth;

void setup() {
  bluetooth.begin();
  lcd.begin();
  relays.begin();
  esp_bluetooth.begin();

  digitalWrite(LED, LOW);

  pinMode(RESET, INPUT);
  attachInterrupt(RESET, reset, FALLING);
  
  static BLEUUID serviceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
  esp_bluetooth.scan();
  Serial.println("Scan finished, trying to connect...");
  while (!esp_bluetooth.connect(serviceUUID)){
    Serial.println("trying to connect");
  }
  blink();
  
}

void loop() {

  while(!bluetooth.receive());
  bluetooth.decode();
  

  lcd.setValues(bluetooth.getValues());
  relays.setValues(bluetooth.getValues());

  lcd.display();

  if (bluetooth.getValue(MODE) == 0) {
    int steps = (int) (bluetooth.getValue(STEPS) / bluetooth.getValue(FRAME));
    int frame = bluetooth.getValue(FRAME);
    int datagramme[] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    for (int i = 0; i < frame; i++) {
      esp_bluetooth.write(datagramme);
      delay(100);
      while (esp_bluetooth.read() != "2"){
        if (bluetooth.receive()){
          bluetooth.decode();

          //si c'est pause, on indique au plateau de faire pause
          if (bluetooth.getValue(PAUSE)!=-1){
            int pause[]={bluetooth.getValue(PAUSE)};
            esp_bluetooth.write(pause);
            // Une fois qu'on est en pause, rester ici car il ne faut pas que le boitier continue de lire son code mais qu'il attente l'instruction qu'il peut reprendre la lecture
            // Des qu'on rappuie sur pause, retirer la data pause = 3 dans android mais garder la totalité de la data avec steps,speed...
            while(!bluetooth.receive());
          }else if (bluetooth.getValue(STOP)!=-1){
            int stop[]={bluetooth.getValue(STOP)};
            esp_bluetooth.write(stop);
          }
        }
      }
      relays.triggerAll();
    }
  }
  else if (bluetooth.getValue(MODE) == 1) {
    int steps = (int) (bluetooth.getValue(STEPS) * bluetooth.getValue(ROTATION_NUMBER));
    int datagramme[] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    esp_bluetooth.write(datagramme);
    delay(100);
    while (esp_bluetooth.read() != "0"){
        if (bluetooth.receive()){
          bluetooth.decode();
          if (bluetooth.getValue(PAUSE)!=-1){
            int pause[]={bluetooth.getValue(PAUSE)};
            esp_bluetooth.write(pause);
            while(!bluetooth.receive());
          }else if (bluetooth.getValue(STOP)!=-1){
            int stop[]={bluetooth.getValue(STOP)};
            esp_bluetooth.write(stop);
          }
        }      
    }
  }

  bluetooth.resetValues();
  lcd.resetValues();

}

void blink(){
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
}
void reset(){
  ESP.restart();
}

  blink();
>>>>>>> master:software/arduino/bloc_commande/bloc_commande/bloc_commande.ino
