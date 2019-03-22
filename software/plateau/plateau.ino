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
  if (nrf.isEmpty()){
    nrf.receive();
  }
  else{
    Serial.println("Data received");
    nrf.printData();
    int acceleration = nrf.getValue(0);
    int speed = nrf.getValue(1);
    int steps = nrf.getValue(2);
    nrf.clear();
    
    motor.setParams(speed, acceleration);
    motor.setZero();
    motor.rotate(steps);
    
    while (motor.isRotating()){
      Serial.println(motor.getCurrentPosition());
      motor.run();
    }
    Serial.println("Rotation finished");
    int data[] = {1};
    nrf.send(data);
  }
}
