


#include "ADisplay.h"
#include "ARTC.h"


ADisplay adisplay;
ARTC rtc;

char message[46] = "Staci ";

char adate[6] = "00:00"; // Aux date
char aalarm[6] = "06:00";// Aux alarm

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! Adafruit ST7735 rotation test");
  adisplay.setup();

  //rtc.setAlarm(aalarm);
  rtc.setAlarm("21:19");
     
}

void loop(void) {
 
  rtc.setHourTimeToMessage(adate);
  rtc.getAlarm(aalarm);
  adisplay.displayDateAlarm(adate, aalarm);
  
  // if it is Alarm time then set the Relay to the AlarmRelayState.
  if(rtc.checkAlarm())
   Serial.println("Alarm");
  else 
   Serial.println("No alarm");
  
  delay(60000);  
}



