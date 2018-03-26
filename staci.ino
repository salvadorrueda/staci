
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
char asetting[6] = "00:00"; // Aux for setting
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
unsigned long ptMillis = 0; // Previous Milis for setHourTimeToMessage
unsigned long pMillis = 0; // Previous Milis for blinking _
unsigned long cMillis = millis(); // Current Milis

const long tinterval = 6000; // RTC and alarm interval to be checked (ms)
const long interval = 500;   // interval at which _ blinks (milliseconds)

int posn = 0; // Pos Alarm digit

void loop(void) {
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
  setting(key);
  /*  
    setting('A'); // Setting an Alarm.
    setting('C'); // Setting Clock hour and minutes'      
  */
  

  if(button.pressed()) {
     mp3.stop();
  }
}

void setting(char key) {
    int color;
    
    switch(key){
    case 'A': 
      //chechForSettingAnAlarm(); // If 'A' is pressent set the Alarm.
      // Setting an Alarm.
      color = ST7735_RED;
      asetting[0]=aalarm[0];
      asetting[1]=aalarm[1];
      asetting[3]=aalarm[3];
      asetting[4]=aalarm[4];
      adisplay.displaySet(adate, aalarm, false, 'a');

///    
    posn = 0;
    while(posn<5) {
      key = keypad.getKey();
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

///   
      aalarm[0]=asetting[0];
      aalarm[1]=asetting[1];
      aalarm[3]=asetting[3];
      aalarm[4]=asetting[4];

      adisplay.displaySet(adate, aalarm, true, 'a');

      rtc.setAlarm(asetting);
      eeprom.eput(asetting);
      break;
    case 'C':
      //checkForSettingClock();   // If 'C' is pressed then sets hour and minutes.
      // Setting Clock hour and minutes'
      color = ST7735_GREEN;
      asetting[0]=adate[0];      
      asetting[1]=adate[1];
      asetting[3]=adate[3];
      asetting[4]=adate[4];
      adisplay.displaySet(adate, aalarm, false, 'c');
      
///
    posn = 0;
    while(posn<5) {
      key = keypad.getKey();
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

///
      adate[0]=asetting[0];
      adate[1]=asetting[1];
      adate[3]=asetting[3];
      adate[4]=asetting[4];
      
      adisplay.displaySet(adate, aalarm, true,'a');

      rtc.setCTime(asetting);
      break;
    }

}

void chechForSettingAnAlarm() {
}

void checkForSettingClock(){
    adisplay.displaySet(adate, aalarm, false, 'c');
       posn = 0;
    while(posn<5) {
      key = keypad.getKey();
      if(key){
        adisplay.setCursorPrintlnColor(posn, key, adate, ST7735_GREEN);

        adate[posn] = key;
        //rtc.setAlarm(aalarm);
        posn++;
        if(posn == 2) posn ++;
        adisplay.setColorBlink(posn, 0, adate, ST7735_GREEN);
       }else{ 
        // blinks _ every interval (500ms)
        cMillis = millis();
        if (cMillis - pMillis >= interval) {
          // save the last time you blinked
          pMillis = cMillis;

          if(b) b = 0; else b = 1;
          adisplay.setColorBlink(posn, b, adate, ST7735_GREEN);
        }
      }
    } // posn 5
    adisplay.displaySet(adate, aalarm, true, 'a');
    //eeprom.eput(aalarm);
    rtc.setCTime(adate);
}


