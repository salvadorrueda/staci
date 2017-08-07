/*
 * Button OOP (Object Oriented Programming)
 * Turns on and off the relay, when a pushbutton attached to pin 2 is pressed.
 * 
 * The circuit:
 * Relay attached to pin 9
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * 
 */

#ifndef _Button_h
#define _Button_h

 #include "Arduino.h"

 
class Button{  
  int buttonPin;     // the number of the pushbutton pin

  // variables will change:
  int buttonState = 0;         // variable for reading the pushbutton status    
  unsigned long buttonDownMs;  // to avoid bouncing recording number of ms button is down


  public:
  Button(int pin);  // Button constructor initializes button object variables
  void setup();     // setup the button object
  int pressed();    // Returns 1 if the button is pressed
};

#endif

