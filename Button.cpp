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

 #include "Arduino.h"
 #include "Button.h"
 
  Button::Button(int pin){
    //Button constructor initializes button object variables
    buttonPin = pin;
    
    buttonState = LOW;         // variable for reading the pushbutton status    
  }

  void Button::setup(){
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
  }

  int Button::pressed(){
    // Returns 1 if the button is pressed
    
    int pressed = 0;
    int lastButtonState = buttonState;     // previous state of the button
    
    buttonState = digitalRead(buttonPin);
    if (lastButtonState == HIGH && buttonState == LOW){
      buttonDownMs = millis();
    }else if (lastButtonState == LOW && buttonState == HIGH){
      if (millis() - buttonDownMs < 50){
        // ignore this for debonce
      }else{
        pressed = 1;
      }   
    }
    return pressed;
  }


