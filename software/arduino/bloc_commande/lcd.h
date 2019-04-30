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
    Lcd(); // constructeur par défaur
    void begin(); // démarre le lcd
    void resetValues(); // réinitialise les données du lcd
    void symboleBluetooth(); // dessine le symbole bluetooth
    void display(); // affiche les données à l'ecran
    void setValues(int *values); // donne les valeurs à afficher au lcd
    void flecheDroite(int absG,int ordB, int absD,int ordH); // dessine la fleche droite
    void flecheGauche(int absG,int ordB, int absD,int ordH); // dessine la fleche gauche
};
