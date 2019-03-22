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
    
    int acceleration = nrf.getValue(ACCELERATION);
    int speed = nrf.getValue(SPEED);
    int direction = nrf.getValue(DIRECTION);
    int steps = nrf.getValue(STEPS);
    int time = nrf.getValue(TIME);
    
    nrf.clear();
    
    motor.setParams(speed, acceleration, direction);

    if (steps >= 0){
      Serial.println("Rotation en nombre de pas");
      motor.setZero();
      motor.rotate(steps);
      
      while (motor.isRotating()){
        Serial.println(motor.getCurrentPosition());
        motor.run();
      }
    }
    else if(time >= 0){
      Serial.println("Rotation en temps");
      long initialTime = millis();
      while (millis()-initialTime < time){
        Serial.println(millis()-initialTime);
        motor.setZero();
        motor.rotate(1);
        motor.run();
      }
    }
    Serial.println("Rotation finished");
    int data[] = {1};
    nrf.send(data);
  }
}
