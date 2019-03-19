#include "nrf.h"
#include "moteur.h"

 

Nrf nrf;
Motor motor;

void setup() {
  Serial.begin(9600);
  
  motor.begin();
  nrf.begin();

}

void loop() {
  nrf.receive();

  if (!nrf.isEmpty()){
      int type = nrf.getValue(0);
      int direction = nrf.getValue(1);
      int frame = nrf.getValue(2);
      int pause = nrf.getValue(3);
      int acceleration = nrf.getValue(4);
      int speed = nrf.getValue(5);

      Serial.print(type);
      Serial.print("\t");
      Serial.print(direction);
      Serial.print("\t");
      Serial.print(frame);
      Serial.print("\t");
      Serial.print(pause);
      Serial.print("\t");
      Serial.print(acceleration);
      Serial.print("\t");
      Serial.println(speed);
      
      motor.setParams(speed, acceleration);

      if (speed > 0){
        for (int i=0; i<frame; i++){
          motor.rotate((int)(STEPS/frame));
          while (motor.isRotating()) motor.run();
          int data[] = {1};
          nrf.send(data);
          delay(pause);
        }
        
      }
  }
}
