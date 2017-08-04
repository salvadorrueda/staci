#include "Arduino.h"
#include "AEEPROM.h"

void AEEPROM::eget(char *amessage){
  // Read from the EEPROM and set the Alarm
  EEPROM.get(_eeAddress, _EAlarm);

  for(int i=0; i<5; i++){
    amessage[i] = _EAlarm._alarm[i];
  }
  
  if(_EAlarm._AState){
    amessage[5] = 'o';
  }else{
    amessage[5] = 'f';
  }

}

void AEEPROM::eput(char *amessage){
  
  for(int i=0; i<5; i++){
    _EAlarm._alarm[i] = amessage[i];
  }
  
  if(amessage[5] == 'o'){
    _EAlarm._AState = 1;
  }else{ // amessage[5] = 'f';
    _EAlarm._AState = 0;
  }
  
  EEPROM.put(_eeAddress, _EAlarm);
}

