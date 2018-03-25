 #include "Arduino.h"
 #include "ARTC.h"

  void ARTC::setHourTimeToMessage(char *message){
    int n0Hour, n1Hour, n0Minute, n1Minute; 
    
    if (RTC.read(_tm)) {
      n0Hour = _tm.Hour/10;
      n1Hour = _tm.Hour-(n0Hour*10);

      n0Minute = _tm.Minute/10;
      n1Minute = _tm.Minute-(n0Minute*10);
       
      message[0]=n0Hour+'0';    
      message[1]=n1Hour+'0';
      message[3]=n0Minute+'0';
      message[4]=n1Minute+'0';
    }        
  }

  int ARTC::checkAlarm(){
    // check if the time is the same of the Alarm 
    // ATriggered. To avoid multiple calls during the alarm (one minute) 

    int n0Hour, n1Hour, n0Minute, n1Minute;
    int isAlarm = 0;
     
    char hourMinute[6] = "00:00";

    if (RTC.read(_tm)) {
      n0Hour = _tm.Hour/10;
      n1Hour = _tm.Hour-(n0Hour*10);

      n0Minute = _tm.Minute/10;
      n1Minute = _tm.Minute-(n0Minute*10);
      hourMinute[0]=n0Hour+'0';    
      hourMinute[1]=n1Hour+'0';
      hourMinute[3]=n0Minute+'0';
      hourMinute[4]=n1Minute+'0';

    int i = 0; 
    while(i<6 && _alarm[i] == hourMinute[i]) i++;
    if (i==6){
        if(!_ATriggered) isAlarm = 1;
        _ATriggered = 1;
      }else{
        _ATriggered = 0; 
      }

    }

    return isAlarm;     
  }

  void ARTC::getAlarm(char *alarm){
    alarm[0] = _alarm[0];
    alarm[1] = _alarm[1];
    alarm[2] = _alarm[2];
    alarm[3] = _alarm[3];
    alarm[4] = _alarm[4];
  }



  void ARTC::setAlarm(char *alarm){
    _alarm[0] = alarm[0];
    _alarm[1] = alarm[1];
    _alarm[2] = alarm[2];
    _alarm[3] = alarm[3];
    _alarm[4] = alarm[4];

    _ATriggered = 0;
  }

  void ARTC::setCTime(char *adate){
    tmElements_t tm; 
    unsigned int H, M; // Hour, Minutes

    H = adate[0]-'0';
    H = H * 10;
    H = H + adate[1]-'0'; 
    tm.Hour = H;

    M = adate[3]-'0';
    M = M * 10;
    M += adate[4]-'0';
    tm.Minute = M;

    RTC.write(tm);   
  }


