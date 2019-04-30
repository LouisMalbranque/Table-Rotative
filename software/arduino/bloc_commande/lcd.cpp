#include "lcd.h"

Lcd::Lcd() {

}

// initialise le lcd
void Lcd::begin() {
  screen.begin( SSD1306_SWITCHCAPVCC, 0x3C );
  screen.clearDisplay();
  //resetValues();
  //display();
}

// réinitualise les valeurs du lcd
void Lcd::resetValues(){
  for (int i=0;i<MAXIMUM_NUMBER_OF_VALUES;i++){
    values[i]=0;
  }
}

// dessine un symbole bluetootj
void Lcd::symboleBluetooth() {
  screen.drawLine( 117, 4, 117, 12, WHITE );
  screen.drawLine( 117, 8 , 115, 10, WHITE );
  screen.drawLine( 117, 8 , 115, 6, WHITE );
  screen.drawLine( 118, 4 , 120, 6, WHITE );
  screen.drawLine( 118, 8 , 120, 10, WHITE );
  screen.drawLine( 118, 8 , 120, 6, WHITE );
  screen.drawLine( 118, 12 , 120, 10, WHITE );
}

// affiche la fleche droite aux abcisses et ordonnées données
void Lcd::flecheDroite(int absG, int ordB, int absD, int ordH) {
  screen.drawLine( absG, ordB, absD, ordH, WHITE );
  screen.drawLine( absD, ordB, absD - 4, ordB + 2, WHITE);
  screen.drawLine( absD, ordB, absD - 4, ordB - 2, WHITE);
}

// affiche la fleche gauche aux abcisses et ordonnées données
void Lcd::flecheGauche(int absG, int ordB, int absD, int ordH) {
  screen.drawLine( absG, ordB, absD, ordH, WHITE );
  screen.drawLine( absG, ordB, absD - 8, ordH + 2, WHITE);
  screen.drawLine( absG, ordB, absD - 8, ordH - 2, WHITE);
}

// affiche les données
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
    screen.println(values[VITESSE]);

    screen.setCursor( 2, 36 );
    screen.print( "Frame=");
    screen.println(values[NOMBRE_DE_PHOTOS]);

    screen.setCursor( 2, 50 );
    screen.print( "NbApp=");
    screen.println(values[NOMBRE_DE_CAMERAS]);

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
    screen.println(values[PAUSE_ENTRE_CAMERAS]);
  }

  else if (values[MODE] == 1) {
    screen.setCursor( 0, 0 );
    screen.println( "Temps Reel" );


    screen.setTextSize( 1 );
    screen.setCursor( 2, 30 );
    screen.println( "Accel=" + (String) values[ACCELERATION] );

    screen.setCursor( 64, 30 );
    screen.println( "Speed=" + (String) values[VITESSE] );

    if (values[TEMPS_DE_ROTATION] >= 0) {
      screen.setCursor( 2, 46 );
      screen.println( "Duree=" + (String) values[TEMPS_DE_ROTATION] );
    }
    else {
      screen.setCursor( 2, 46 );
      screen.println( "NbTours=" + (String) values[NOMBRE_DE_TOUR] );
    }

    screen.setCursor( 64, 46 );
    screen.println( "Sens:");
    if (values[DIRECTION] == 0) {
      flecheDroite(98, 49, 110, 49);
    }
    else {
      flecheGauche(98, 49, 110, 49);
    }

  }
  symboleBluetooth();
  screen.display();
}

// donne ses valeurs au LCD pour l'affichage
void Lcd::setValues(int *values) {
  for (int i = 0; i < MAXIMUM_NUMBER_OF_VALUES; i++) {
    this->values[i] = values[i];
  }
}
