#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "arduino.h"
#include "constantes.h"


class Lcd
{
  private:  
    Adafruit_SSD1306 screen = *(new Adafruit_SSD1306(OLED_RESET));
    int values[MAXIMUM_NUMBER_OF_VALUES];
  public:
    Lcd();
    void begin();
    void resetValues();
    void symboleBluetooth();
    void display();
    void setValues(int *values);
    void flecheDroite(int absG,int ordB, int absD,int ordH);
    void flecheGauche(int absG,int ordB, int absD,int ordH);
};
