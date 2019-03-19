#include "lcd.h"

Lcd::Lcd(){
  
}
void Lcd::begin(){
  screen.begin( SSD1306_SWITCHCAPVCC, 0x3C );
  screen.clearDisplay();
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

void Lcd::flecheDroite() {
  screen.drawLine( 117, 4, 117, 12, WHITE );
  screen.drawLine( 117, 8 , 115, 10, WHITE );
  screen.drawLine( 117, 8 , 115, 6, WHITE );
  screen.drawLine( 118, 4 , 120, 6, WHITE );
  screen.drawLine( 118, 8 , 120, 10, WHITE );
  screen.drawLine( 118, 8 , 120, 6, WHITE );
  screen.drawLine( 118, 12 , 120, 10, WHITE );
}

void Lcd::flecheGauche() {
  screen.drawLine( 117, 4, 117, 12, WHITE );
  screen.drawLine( 117, 8 , 115, 10, WHITE );
  screen.drawLine( 117, 8 , 115, 6, WHITE );
  screen.drawLine( 118, 4 , 120, 6, WHITE );
  screen.drawLine( 118, 8 , 120, 10, WHITE );
  screen.drawLine( 118, 8 , 120, 6, WHITE );
  screen.drawLine( 118, 12 , 120, 10, WHITE );
}

void Lcd::display() {
  
  screen.setTextSize(2);
  screen.setTextColor(WHITE);
  screen.clearDisplay();
  screen.drawRect( 0, 18, screen.width() - 2, screen.height() - 20, WHITE );

  if(values[0]==0){
  screen.setCursor( 0, 0 );
  screen.println( "Programme" );

  
  screen.setTextSize( 1 );
  screen.setCursor( 2, 22 );
  screen.println( "Accel=" + (String) values[6] );

  screen.setCursor( 64, 22 );
  screen.println( "Speed=" + (String) values[7] );

  screen.setCursor( 2, 36 );
  screen.println( "Frame=" + (String) values[2] );

  screen.setCursor( 64, 36 );
  screen.println( "NbApp=" + (String) values[3] );

  screen.setCursor( 2, 50 );
  screen.println( "Sens=" + (String) values[1] );

  screen.setCursor( 64, 50 );
  screen.println( "Pause=" + (String) values[5] );
  }
  
  else if (values[0]==1){
    screen.setCursor( 0, 0 );
  screen.println( "Temps Reel" );

  
  screen.setTextSize( 1 );
  screen.setCursor( 2, 22 );
  screen.println( "Accel=" + (String) values[2] );

  screen.setCursor( 64, 22 );
  screen.println( "Speed=" + (String) values[3] );

  if(values[4]!=0){
  screen.setCursor( 2, 36 );
  screen.println( "Duree=" + (String) values[4] );}
  else{
    screen.setCursor( 2, 36 );
  screen.println( "NbTours=" + (String) values[5] );
  }

  screen.setCursor( 64, 36 );
  screen.println( "Sens=" + (String) values[1] );



  }
  symboleBluetooth();
  screen.display();
}

void Lcd::setValues(int *values){
  for (int i=0; i<MAXIMUM_NUMBER_OF_VALUES; i++){
    this->values[i] = values[i];
  }
}
