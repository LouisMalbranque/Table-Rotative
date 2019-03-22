#include  "bluetooth.h"
#include  "nrf.h"
#include  "relays.h"
#include  "lcd.h"
#include  "instruction.h"
#include "constantes.h"

Lcd lcd;
Relays relays;
Bluetooth bluetooth;
Nrf nrf;


void setup() {
  bluetooth.begin();
  lcd.begin();
  nrf.begin();
  relays.begin();
}

void loop() {
  
  bluetooth.receive();
  bluetooth.decode();

  lcd.setValues(bluetooth.getValues());
  lcd.display();

  int steps = (int) (bluetooth.getValue(STEPS) / bluetooth.getValue(FRAME));
  int datagramme[3] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), steps};

  relays.setValues(bluetooth.getValues());
  
  for (int i = 0; i < bluetooth.getValue(FRAME); i++) {
    nrf.send(datagramme);
    while (nrf.getValue(0) != 1) {
      nrf.receive();
    }
    relays.triggerAll();
  }
  bluetooth.resetValues();
  lcd.resetValues();

}
