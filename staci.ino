


#include "ADisplay.h"


ADisplay adisplay;

char message[6] = "00:00";
void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! Adafruit ST7735 rotation test");
  adisplay.setup();
  
  adisplay.println(message);  
}

void loop(void) {
 
  
}



