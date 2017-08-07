

#include "ADisplay.h"
#include "ARTC.h"
#include "AEEPROM.h"
#include "Akeypad.h"
#include "SerialMP3Player.h"
#include "Button.h"

ADisplay adisplay;
ARTC rtc;
AEEPROM eeprom;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
SerialMP3Player mp3;
Button button(2);   // Button attached on pin 2




char message[46] = "Staci ";

char adate[6] = "00:00"; // Aux date
char aalarm[7] = "06:00";// Aux alarm
char odate[6] = "00:00"; // Old date

void setup(void) {
  Serial.begin(9600);
  adisplay.setup();
    
  eeprom.eget(aalarm);
  rtc.setAlarm(aalarm);
  
  mp3.begin(9600);
  mp3.sendCommand(CMD_SEL_DEV, 0, 2);
  delay(500);

  button.setup();
}

char key;
int b = 0; // Blink black or red.
unsigned long pMillis = 0; // Previous Milis
unsigned long cMillis = millis(); // Current Milis
const long interval = 500;       // interval at which to blink (milliseconds)
int posn = 0; // Pos Alarm digit 
 


void loop(void) {
  
  rtc.setHourTimeToMessage(adate);
  rtc.getAlarm(aalarm);
  
  adisplay.displayDateAlarm(odate, adate, aalarm);

  chechForSettingAnAlarm();
   
  if(rtc.checkAlarm()){
   Serial.println("Alarm");
   mp3.sendCommand(CMD_FOLDER_CYCLE, 1, 0); 
  }
  // else 
  // Serial.println("No alarm");   

  if(button.pressed()) {
     mp3.stop();
  }
 

}

  void chechForSettingAnAlarm(){
 
  key = keypad.getKey();
 if(key=='A'){
    //Serial.print(key);
    adisplay.displaySetAlarm(adate, aalarm, false);
    posn = 0;
    while(posn<5){
      key = keypad.getKey();
      if(key){
                                       
          adisplay.setCursorPrintln(posn, key, aalarm); 
          
          aalarm[posn] = key;
          rtc.setAlarm(aalarm);  
          posn++;
          if(posn == 2) posn ++;
          adisplay.setAlarmBlink(posn, 0, aalarm);


      }else{
          cMillis = millis();
          if (cMillis - pMillis >= interval) {
          // save the last time you blinked the LED
          pMillis = cMillis;

          if(b) b = 0; else b = 1;
          adisplay.setAlarmBlink(posn, b, aalarm);
          }          
      }      
    } // posn 5    
    adisplay.displaySetAlarm(adate, aalarm, true);
    eeprom.eput(aalarm);
    
  } // Key == A
}




