#include  "bluetooth.h"
#include  "nrf.h"
#include  "relays.h"
#include  "lcd.h"
#include  "instruction.h"
#include  "Queue.h"

Lcd lcd;
Relays relays;
Bluetooth bluetooth;
Nrf nrf;

Queue<Instruction> instructionQueue = Queue<Instruction>(4);

void dummy1(void){
  bluetooth.print("dummy1");
}
void dummy2(void){
  bluetooth.print("dummy2");
}
void setup() {
  
  lcd.begin();
  bluetooth.begin();
  nrf.begin();
}

void loop() {  
  if (bluetooth.receive()){
    bluetooth.decode();
  /*
    if (true){
      Instruction inst(&dummy1);
      instructionQueue.push(inst);
    }
    else{
      Instruction inst(&dummy2);
      instructionQueue.push(inst);
    }
  */
    lcd.setValues(bluetooth.getValues());
    lcd.display();

    int steps = blietooth.getValue(STEPS) / bluetooth.getValue(NB_PHOTOS);
    int datagramme[] = {bluetooth.getValue(ACCELERATION),bluetooth.getValue(SPEED),};
    nrf.send(datagramme);
  
    for (int i=0; i<bluetooth.getValue(FRAME); i++){
      while (nrf.getValue(0) != 1){
        nrf.receive();
        bluetooth.print(i);
      }
      relays.triggerSimultaneous();
    }
    bluetooth.reset(); 
  /*
    while (instructionQueue.count() != 0){
      instructionQueue.pop().run();
    }
  */
  }
}
