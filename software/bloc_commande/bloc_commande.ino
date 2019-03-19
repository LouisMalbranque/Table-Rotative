#include  "bluetooth.h"
#include  "nrf.h"
#include  "relays.h"
#include  "lcd.h"

Lcd lcd;
Relays relays;
Bluetooth bluetooth;
Nrf nrf;


void setup() {
  lcd.begin();
  bluetooth.begin();
  nrf.begin();
  
  pinMode(3, OUTPUT);
  digitalWrite(3,LOW);
}

void loop() {
  
  bluetooth.receive();
  bluetooth.decode();
  
  lcd.setValues(bluetooth.getValues());
  lcd.display();
  
  nrf.send(bluetooth.getValues());

  for (int i=0; i<bluetooth.getValue(FRAME); i++){
    while (nrf.getValue(0) != 1){
      nrf.receive();
    }
    relays.triggerSimultaneous();
  }  
}
