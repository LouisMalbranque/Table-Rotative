#include  "bluetooth.h"
#include  "nrf.h"
#include  "relays.h"
#include  "lcd.h"

Lcd screen;
Relays relays;
Bluetooth bluetooth;
int values[8] = {8,7,6,5,4,3,2,1};
void setup() {
  screen.begin();
  bluetooth.begin();
   pinMode(3, OUTPUT);
   digitalWrite(3,LOW);
 pinMode(2, OUTPUT);
   digitalWrite(2,LOW);
}

void loop() {

  
  bluetooth.receive();
  int *values=bluetooth.decode();
  screen.setValues(values);
  relays.setValues(values);
  screen.display();
  relays.triggerAll();
}
