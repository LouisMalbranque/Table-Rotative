#include "constantes.h"

#include  "bluetooth.h"
#include  "lcd.h"
#include  "nrf.h"
#include  "relays.h"


Bluetooth bluetooth;
Lcd lcd;
Nrf nrf;
Relays relays;



void setup() {
  bluetooth.print("test");
  bluetooth.begin();
  bluetooth.print("2");
  lcd.begin();
  bluetooth.print("3");
  nrf.begin();
  bluetooth.print("4");
  relays.begin();
  bluetooth.print("5");
}

void loop() {

  bluetooth.receive();

  bluetooth.decode();

  lcd.setValues(bluetooth.getValues());
  relays.setValues(bluetooth.getValues());

  lcd.display();

  if (bluetooth.getValue(MODE) == 0) {
    int steps = (int) (bluetooth.getValue(STEPS) / bluetooth.getValue(FRAME));
    int datagramme[NRF_DATA_LENGTH] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    for (int i = 0; i < bluetooth.getValue(FRAME); i++) {
      nrf.send(datagramme);
      while (nrf.getValue(0) != 1) {
        nrf.receive();
      }
      relays.triggerAll();
    }
  }
  else if (bluetooth.getValue(MODE) == 1) {
    int steps = (int) (bluetooth.getValue(STEPS) * bluetooth.getValue(ROTATION_NUMBER));
    int datagramme[NRF_DATA_LENGTH] = {bluetooth.getValue(ACCELERATION), bluetooth.getValue(SPEED), bluetooth.getValue(DIRECTION), steps , bluetooth.getValue(ROTATION_TIME)};
    nrf.send(datagramme);
    while (nrf.getValue(0) != 1) {
      nrf.receive();
    }
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
  }

  bluetooth.resetValues();
  lcd.resetValues();
  nrf.clear();

}
