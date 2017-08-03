 #include "Arduino.h"
 #include "ARTC.h"

  void ARTC::setHourTimeToMessage(char *message){
    int n0Hour, n1Hour, n0Minute, n1Minute; 
    
    if (RTC.read(tm)) {
      n0Hour = tm.Hour/10;
      n1Hour = tm.Hour-(n0Hour*10);

      n0Minute = tm.Minute/10;
      n1Minute = tm.Minute-(n0Minute*10);
       
      message[0]=n0Hour+'0';    
      message[1]=n1Hour+'0';
      message[3]=n0Minute+'0';
      message[4]=n1Minute+'0';
    }

    message[10]=alarm[0];
    message[11]=alarm[1];
    message[12]=alarm[2];
    message[13]=alarm[3];
    message[14]=alarm[4];

    if(ARelayState){
      message[18]='0';
      message[19]='N';
      message[20]=' ';
    }else{
      message[18]='O';
      message[19]='F';
      message[20]='F';
    }
        
  }

  int ARTC::checkAlarm(){
    // check if the time is the same of the Alarm 
    // ATriggered. To avoid multiple calls during the alarm (one minute) 
    
    int n0Hour, n1Hour, n0Minute, n1Minute;
    int isAlarm = 0;
     
    char hourMinute[6] = "00:00";

    if (RTC.read(tm)) {
      n0Hour = tm.Hour/10;
      n1Hour = tm.Hour-(n0Hour*10);

      n0Minute = tm.Minute/10;
      n1Minute = tm.Minute-(n0Minute*10);
      hourMinute[0]=n0Hour+'0';    
      hourMinute[1]=n1Hour+'0';
      hourMinute[3]=n0Minute+'0';
      hourMinute[4]=n1Minute+'0';
    }

    int i = 0; 
    while(i<6 && alarm[i] == hourMinute[i]) i++;
    if (i==6){
        if(!ATriggered) isAlarm = 1;
        ATriggered = 1;
      }else{
        ATriggered = 0; 
      }
    
    return isAlarm;     
  }

  int ARTC::getAlarmRelayState(){
    return ARelayState;
  }

  void ARTC::setAlarmRelayState(int state){
    ARelayState = state;
  }

  void ARTC::setAlarmRelay(char *malarm){
    alarm[0] = malarm[0];
    alarm[1] = malarm[1];
    alarm[2] = malarm[2];
    alarm[3] = malarm[3];
    alarm[4] = malarm[4];
  }



