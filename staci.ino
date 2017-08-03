


#include "ADisplay.h"
#include "ARTC.h"


ADisplay adisplay;
ARTC rtc;

char message[6] = "00:00";
char oldmessage[6] = "00:00";

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! Adafruit ST7735 rotation test");
  adisplay.setup();
   
}

void loop(void) {
 
  rtc.setHourTimeToMessage(message);
  adisplay.println(message);  
    
  delay(60000);  

}



