#include  "bluetooth.h"
#include  "nrf.h"
#include  "relays.h"
#include  "lcd.h"

Lcd screen;
Relays relays;
Bluetooth bluetooth;
int values[9] = {9,8,7,6,5,4,3,2,1};
void setup() {
  screen.begin();
  bluetooth.begin();
}

void loop() {

  //relays.triggerAll();
  bluetooth.receive();
  screen.setValues(bluetooth.decode());

  screen.display();
}
