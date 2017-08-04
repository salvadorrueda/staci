#ifndef _AEEPROM_h
#define _AEEPROM_h

 #include <EEPROM.h>
 #include "Arduino.h"

 class AEEPROM{
  
  struct EEPROMAlarm {
   char _alarm[6]; // 00:00
   int _AState;    // 1 > On, 0 > Off
  } _EAlarm {"06:00",0}; 
 
  //EEPROMAlarm EAlarm {"06:00",1};
  
  int _eeAddress = 0; //EEPROM address to start reading from

  public:
  void eget(char *amessage); // Read from the EEPROM and set the Alarm
  void eput(char *amessage);  // Write an Alarm to the EEPROM
 };


#endif

