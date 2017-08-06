


#include "ADisplay.h"
#include "ARTC.h"
#include "AEEPROM.h"
#include "Akeypad.h"


ADisplay adisplay;
ARTC rtc;
AEEPROM eeprom;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


char message[46] = "Staci ";

char adate[6] = "00:00"; // Aux date
char aalarm[7] = "06:00";// Aux alarm
char odate[6] = "00:00"; // Old date

void setup(void) {
  Serial.begin(9600);
  //Serial.print("Hello! Adafruit ST7735 rotation test");
  adisplay.setup();

  //eeprom.eput("06:08o");
  
  eeprom.eget(aalarm);
  rtc.setAlarm(aalarm);
  //rtc.setAlarm("21:19");
     
}

char key;
bool next = false;
int j = 0;

void loop(void) {
  
  rtc.setHourTimeToMessage(adate);
  rtc.getAlarm(aalarm);
  
  adisplay.displayDateAlarm(odate, adate, aalarm); 

  

 /* 
  if(rtc.checkAlarm())
   Serial.println("Alarm");
  else 
   Serial.println("No alarm");
  
 */   
/*
  for(int i = 0; i<1000; i++){
    key = keypad.getKey();
    if(key=='A'){
      //Serial.print(key);
      adisplay.displaySetAlarm(adate, aalarm);
      next = false;
      while(!next){
        key = keypad.getKey();
        if(key){
          //tft.setCursor(35, 80);
          //tft.println(key);
          
          adisplay.setCursorPrintln(35, 80, key);  
          next = true;
        }else{
          adisplay.setAlarmBlink(35,j%2);          
        }
        j++;
        delay(500);
      }
      
    } // Key == A
    
    delay(60);
  }
  
 */
  
}



