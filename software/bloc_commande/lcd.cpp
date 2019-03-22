#include "lcd.h"

Lcd::Lcd() {

}
void Lcd::begin() {
  screen.begin( SSD1306_SWITCHCAPVCC, 0x3C );
  screen.clearDisplay();
  //resetValues();
  //display();
}
void Lcd::resetValues(){
  for (int i=0;i<MAXIMUM_NUMBER_OF_VALUES;i++){
    values[i]=0;
  }
}
void Lcd::symboleBluetooth() {
  screen.drawLine( 117, 4, 117, 12, WHITE );
  screen.drawLine( 117, 8 , 115, 10, WHITE );
  screen.drawLine( 117, 8 , 115, 6, WHITE );
  screen.drawLine( 118, 4 , 120, 6, WHITE );
  screen.drawLine( 118, 8 , 120, 10, WHITE );
  screen.drawLine( 118, 8 , 120, 6, WHITE );
  screen.drawLine( 118, 12 , 120, 10, WHITE );
}

void Lcd::flecheDroite(int absG, int ordB, int absD, int ordH) {
  screen.drawLine( absG, ordB, absD, ordH, WHITE );
  screen.drawLine( absD, ordB, absD - 4, ordB + 2, WHITE);
  screen.drawLine( absD, ordB, absD - 4, ordB - 2, WHITE);
}

void Lcd::flecheGauche(int absG, int ordB, int absD, int ordH) {
  screen.drawLine( absG, ordB, absD, ordH, WHITE );
  screen.drawLine( absG, ordB, absD - 8, ordH + 2, WHITE);
  screen.drawLine( absG, ordB, absD - 8, ordH - 2, WHITE);
}

void Lcd::display() {

  screen.setTextSize(2);
  screen.setTextColor(WHITE);
  screen.clearDisplay();
  screen.drawRect( 0, 18, screen.width() - 2, screen.height() - 20, WHITE );

  if (values[MODE] == 0) {
    screen.setCursor( 0, 0 );
    screen.println( "Programme" );


    screen.setTextSize( 1 );
    screen.setCursor( 2, 22 );
    screen.print( "Accel=");
    screen.println(values[ACCELERATION]);

    screen.setCursor( 64, 22 );
    screen.print( "Speed=");
    screen.println(values[SPEED]);

    screen.setCursor( 2, 36 );
    screen.print( "Frame=");
    screen.println(values[FRAME]);

    screen.setCursor( 2, 50 );
    screen.print( "NbApp=");
    screen.println(values[CAMERA_NUMBER]);

    screen.setCursor( 64, 36 );
    screen.println( "Sens:" );
    if (values[DIRECTION] == 0) {
      flecheDroite(98, 39, 110, 39);
    }
    else {
      flecheGauche(98, 39, 110, 39);
    }

    screen.setCursor( 64, 50 );
    screen.print( "Pause=");
    screen.println(values[PAUSE]);
  }

  else if (values[0] == 1) {
    screen.setCursor( 0, 0 );
    screen.println( "Temps Reel" );


    screen.setTextSize( 1 );
    screen.setCursor( 2, 30 );
    screen.println( "Accel=" + (String) values[2] );

    screen.setCursor( 64, 30 );
    screen.println( "Speed=" + (String) values[3] );

    if (values[4] != 0) {
      screen.setCursor( 2, 46 );
      screen.println( "Duree=" + (String) values[4] );
    }
    else {
      screen.setCursor( 2, 46 );
      screen.println( "NbTours=" + (String) values[5] );
    }

    screen.setCursor( 64, 46 );
    screen.println( "Sens:");
    if (values[1] == 0) {
      flecheDroite(98, 49, 110, 49);
    }
    else {
      flecheGauche(98, 49, 110, 49);
    }

  }
  symboleBluetooth();
  screen.display();
}

void Lcd::setValues(int *values) {
  for (int i = 0; i < MAXIMUM_NUMBER_OF_VALUES; i++) {
    this->values[i] = values[i];
  }
}
