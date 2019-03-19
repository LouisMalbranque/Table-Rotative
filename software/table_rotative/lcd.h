#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "arduino.h"
#define OLED_RESET 4
#define MAXIMUM_NUMBER_OF_VALUES 16

class Lcd
{
  private:  
    Adafruit_SSD1306 screen = new Adafruit_SSD1306(OLED_RESET);
    int values[MAXIMUM_NUMBER_OF_VALUES];
  public:
    Lcd();
    void begin();
    void symboleBluetooth();
    void display();
    void setValues(int *values);
    void flecheDroite();
    void flecheGauche();
};
