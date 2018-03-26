
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

char adate[7] = "00:00"; // Aux date
char aalarm[7] = "06:00";// Aux alarm
char asetting[7] = "00:00"; // Aux for setting
char odate[7] = "00:00"; // Old date

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
unsigned long ptMillis = 0; // Previous Milis for setHourTimeToMessage
unsigned long pMillis = 0; // Previous Milis for blinking _
unsigned long cMillis = millis(); // Current Milis

const long tinterval = 6000; // RTC and alarm interval to be checked (ms)
const long interval = 500;   // interval at which _ blinks (milliseconds)

int posn = 0; // Position of the digit on Alarm / Clock setting.

void loop(void) {

  // wait "tinterval" to check for time from the RTC.
  cMillis = millis();
  if (cMillis - ptMillis >= tinterval) {
    // save the last time you blinked
    ptMillis = cMillis;

    rtc.setHourTimeToMessage(adate);
    rtc.getAlarm(aalarm);

    adisplay.displayDateAlarm(odate, adate, aalarm);

    if(rtc.checkAlarm()){
      // Serial.println("Alarm");
      mp3.sendCommand(CMD_FOLDER_CYCLE, 1, 0);
    }
  }

  key = keypad.getKey();
  if(key) setting(key);
  
  /*  
    setting('A'); // Setting an Alarm.
    setting('C'); // Setting Clock hour and minutes'      
  */

  if(button.pressed()) {
     mp3.stop();
  }
}

void getSettingsFromKeys(int color){
  // Take the digits for the Alarm or Clock
    posn = 0;
    while(posn<5) {
      key = keypad.getKey();
      if(key) Serial.println(key);
  
      if(key){
        adisplay.setCursorPrintlnColor(posn, key, asetting, color);

        asetting[posn] = key;
        //rtc.setAlarm(aalarm);
        posn++;
        if(posn == 2) posn ++;
        adisplay.setColorBlink(posn, 0, asetting, color);
       }else{ 
        // blinks _ every interval (500ms)
        cMillis = millis();
        if (cMillis - pMillis >= interval) {
          // save the last time you blinked
          pMillis = cMillis;

          if(b) b = 0; else b = 1;
          adisplay.setColorBlink(posn, b, asetting, color);
        }
      }
    } // posn 5
  
}

void setting(char key) {
  // Set an Alarm or the Clock
  //    'A' for Alarm
  //    'C' for Clock

    int color;
    
    switch(key){
    case 'A': 
      //chechForSettingAnAlarm(); // If 'A' is pressent set the Alarm.
      // Setting an Alarm.
      color = ST7735_RED;
      strcpy(asetting,aalarm);
      
      adisplay.displaySet(adate, aalarm, false, 'a');

      getSettingsFromKeys(color);

      strcpy(aalarm,asetting);
 
      adisplay.displaySet(adate, aalarm, true, 'a');

      rtc.setAlarm(asetting);
      eeprom.eput(asetting);
      break;
    case 'C':
      //checkForSettingClock();   // If 'C' is pressed then sets hour and minutes.
      // Setting Clock hour and minutes'
      color = ST7735_GREEN;
      strcpy(asetting,adate);
 
      adisplay.displaySet(adate, aalarm, false, 'c');

      getSettingsFromKeys(color);

      strcpy(adate,asetting);
 
      adisplay.displaySet(adate, aalarm, true,'a');

      rtc.setCTime(asetting);
      break;
    }

}

