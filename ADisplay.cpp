 #include "Arduino.h"
 #include "ADisplay.h"

/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void ADisplay::setup(){
    // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  //tft.setTextWrap(false); // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1); // landscape 
}

void ADisplay::println(char *msg){
     tft.fillScreen(ST7735_BLACK);
   //
   //Serial.println(tft.getRotation(), DEC);
 
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.setTextColor(ST7735_WHITE);
    tft.println(msg);  
 
}

int strcmpn(char *odate, char *date){
  // Return the index of the diff or -1 if the two are the same.
  
  int j = 0;
  bool e = true; // equals

  // strlen (date) -> 6
  while (j<6 && e){
    if(odate[j]==date[j]) j++;
    else e = false;
  }

  if (j==6) return -1;
  else return j;
}

void ADisplay::displayDateAlarm(char *odate, char *date, char *alarm){
  
    int change;
    
    change = strcmpn(date,odate);
    
    if(change != -1){
        
      //tft.fillScreen(ST7735_BLACK);
   
      tft.setCursor(5+(30*change), 30);
      tft.setTextSize(5);
      tft.setTextColor(ST7735_BLACK);
      tft.println(odate+change);  
  
      tft.setCursor(5, 30);
      tft.setTextSize(5);
      tft.setTextColor(ST7735_GREEN);
      tft.println(date);        
      
      tft.setCursor(35, 80);
      tft.setTextSize(3);
      tft.setTextColor(ST7735_RED);
      tft.println(alarm);  
  
      odate[0]=date[0];
      odate[1]=date[1];
      odate[3]=date[3];
      odate[4]=date[4];
  }
  
}

void ADisplay::setColorBlink(int posn, bool black, char *alarm, unsigned int color){

    tft.setCursor(35+posn*18, 80);
   
    if(black){
      tft.setTextColor(color); // ST7735_RED or ST7735_GREEN 
    }else{
      tft.setTextColor(ST7735_BLACK);
    }
    
    tft.println("_");

    tft.setTextColor(color);
    tft.setCursor(35, 80);
    tft.println(alarm);
  }

  

void ADisplay::setCursorPrintlnColor(int posn, char key, char *alarm, unsigned int color){
    int posn1 = posn;
    
    setColorBlink(posn, 0, alarm, color);

    tft.setCursor(35, 80);
    tft.setTextColor(ST7735_BLACK);
    tft.println(alarm);
    
    
    tft.setTextColor(color);
    tft.setCursor(35+(posn*18), 80);
    tft.println(key); 
}

void ADisplay::displaySet(char *date, char *alarm, bool settled, char type){
// "type" 'c' for setting clock and 'a' for setting an alarm.

    char header_text[14]="setting clock"; // or setting alarm.
    int c = ST7735_GREEN; // color  
    char *setting;

    if (type == 'c'){ // setting clock
      strcpy(header_text,"setting clock");
      c = ST7735_GREEN;
      setting = date;
      
    }else{ // setting an alarm
      strcpy(header_text,"setting alarm");
      c = ST7735_RED;
      setting = alarm;
    }


      tft.fillScreen(ST7735_BLACK);
  
      tft.setCursor(0, 0);
      tft.setTextSize(2);

      if(settled) tft.setTextColor(ST7735_BLACK); 
      else tft.setTextColor(ST7735_RED);

      tft.println(header_text);  // setting clock or alarm

      tft.setCursor(5, 30);
      tft.setTextSize(5);
      tft.setTextColor(ST7735_GREEN);
      tft.println(date);  
  
      tft.setCursor(35, 80);
      tft.setTextSize(3);
      tft.setTextColor(c);
      tft.println(setting);   
}







