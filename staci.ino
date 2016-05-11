/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// RTC DS1307
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

// DHT11

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

/***********************************************************/
// Demo for the Serial MP3 Player Catalex (YX5300 chip)
// Hardware: Serial MP3 Player *1
// Board:  Arduino
// http://www.dx.com/p/uart-control-serial-mp3-music-player-module-for-arduino-avr-arm-pic-blue-silver-342439#.VfHyobPh5z0 
//
// 
//


// Uncomment SoftwareSerial for Arduino Uno or Nano.  

//#include <SoftwareSerial.h>

//#define ARDUINO_RX 5  //should connect to TX of the Serial MP3 Player module
//#define ARDUINO_TX 6  //connect to RX of the module

//SoftwareSerial mp3(ARDUINO_RX, ARDUINO_TX);

#define mp3 Serial3    // Connect the MP3 Serial Player to the Arduino MEGA Serial3 (14 TX3 -> RX, 15 RX3 -> TX)

static int8_t Send_buf[8] = {0}; // Buffer for Send commands.  
static uint8_t ansbuf[10] = {0}; // Buffer for the answers.    
int iansbuf = 0;                 // Index for answer buffer.
String mp3answer;                // Answer from the MP3.   
 
static int8_t pre_vol, volume = 0x0f; // Volume. 0-30 DEC values. 0x0f = 15. 


boolean playing = false;    // Sending 'p' the module switch to Play to Pause or viceversa.   

/************ Command byte **************************/
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play.
#define CMD_SEL_DEV       0X09
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F

#define CMD_STOP_PLAY     0X16
#define CMD_FOLDER_CYCLE  0X17
#define CMD_SHUFFLE_PLAY  0x18 //
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle.

#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01
  
#define CMD_PLAY_W_VOL    0X22
#define CMD_PLAYING_N     0x4C

/************ Opitons **************************/  
#define DEV_TF            0X02  
#define SINGLE_CYCLE_ON   0X00
#define SINGLE_CYCLE_OFF  0X01


/*********************************************************************/

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! STACI ST7735 TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  dht.begin();

  mp3.begin(9600);
  delay(500);
                                          
        sendCommand(CMD_SEL_DEV, DEV_TF);  
  delay(200);
//  sendCommand(CMD_PLAY_W_VOL, 0X0F28); // Playing a 15 (0x0F) Vol the song num 40 (0x28). 


/// For testing porpuses, per no repetir en el loop
  gettime();
  
  tft.setCursor(0, 20); // x, y
  getdht();


}


void loop() 
{
 char c=' ';
  
  // If there a char on Serial call sendMP3Command to sendCommand
   if( Serial.available() )
    {
    c = Serial.read();
    sendMP3Command(c);
    }
    
  // Check for the answer.
  if (mp3.available())
  {
    Serial.println(decodeMP3Answer());
  }
  delay(100);
}


void gettime(){
  
  tmElements_t tm;

  if (RTC.read(tm)) {

  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(2);
  tft.print(" Hi ");
  tft.setTextColor(ST7735_WHITE);
  tft.print("");
  tft.print(tm.Hour);
  tft.print(':');
  tft.print(tm.Minute);

  delay(1000);

    /*
    
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  */  
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
  }

void getdht(){
   // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

//    tft.print("Humidity: ");
//    tft.print(h);
//    tft.print(" %\t");
//    tft.print("Temperature: ");
    tft.print(t);
    tft.print(" *C ");
//    tft.print(f);
//    tft.print(" *F\t");
//    tft.print("Heat index: ");
//    tft.print(hic);
//    tft.print(" *C ");
//    tft.print(hif);
//    tft.println(" *F"); 
  
  }
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}



 
/********************************************************************************/
/*Function sendMP3Command: seek for a 'c' command and send it to MP3  */
/*Parameter: c. Code for the MP3 Command, 'h' for help.                                                                                                         */
/*Return:  void                                                                */

void sendMP3Command(char c){
    switch (c) {
    case '?':
    case 'h':
          Serial.println("HELP  ");
          Serial.println(" p > Play / Pause ");
          Serial.println(" n > Next");          
          Serial.println(" b > Previous");
          Serial.println(" u > Volume UP");
          Serial.println(" d > Volume DOWN");
      break;
                 
     
      case 'p':
          if(!playing){
            Serial.println("Play ");
            //sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class
            sendCommand(CMD_PLAY, 0);
            playing = true;
          }else{
            Serial.println("Pause");
            sendCommand(CMD_PAUSE, 0);
             playing = false;           
          }
      break;

      
      case 'n':
          Serial.println("Next");
          sendCommand(CMD_NEXT_SONG, 0);
          sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      break;
      
      
      case 'b':
          Serial.println("Previous");
          sendCommand(CMD_PREV_SONG, 0);
          sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
      break;
     
      case 'u':
          Serial.println("Volume Up");
          sendCommand(CMD_VOLUME_UP, 0);
      break;

      case 'd':
          Serial.println("Volume Down");
          sendCommand(CMD_VOLUME_DOWN, 0);
      break;
      
    }
}


 
/********************************************************************************/
/*Function decodeMP3Answer: Decode MP3 answer.                                  */
/*Parameter:-void                                                               */
/*Return: The                                                  */

String decodeMP3Answer(){
  String decodedMP3Answer="";
  
      decodedMP3Answer+=sanswer();
  // we have at all message? or just part of it?
  // if iansbuf is zero is because it was reset to it when 0xEF (end) was readed.  
   if(iansbuf==0)
    {   
     switch (ansbuf[3])
     {
      case 0x3A:
         decodedMP3Answer+=" -> Memory card inserted.";
         break; 
         
      case 0x3D:
         decodedMP3Answer+=" -> Completed play num "+String(ansbuf[6],DEC);
         break; 
         
      case 0x4C:
         decodedMP3Answer+=" -> Playing: "+String(ansbuf[6],DEC);
         break;
      
      case 0x41:
         decodedMP3Answer+=" -> Data recived correctly. ";
         break;     
     } 
    }  
   return decodedMP3Answer;
 }  


 
 


/********************************************************************************/
/*Function: Send command to the MP3                                         */
/*Parameter:-int8_t command                                                     */
/*Parameter:-int16_ dat  parameter for the command                              */

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e;   //
  Send_buf[1] = 0xff;   //
  Send_buf[2] = 0x06;   // Len 
  Send_buf[3] = command;//
  Send_buf[4] = 0x01;   // 0x00 NO, 0x01 feedback
  Send_buf[5] = (int8_t)(dat >> 8);  //datah
  Send_buf[6] = (int8_t)(dat);       //datal
  Send_buf[7] = 0xef;   //
  for(uint8_t i=0; i<8; i++)
  {
    mp3.write(Send_buf[i]) ;
  }
  
}



/********************************************************************************/
/*Function: sbyte2hex. Returns a byte data in HEX format.                 */
/*Parameter:- uint8_t b. Byte to convert to HEX.                                */
/*Return: String                                                                */


String sbyte2hex(uint8_t b)
{
  String shex;
  
  //Serial.print("0x");
  shex="0X";
  
  //if (b < 16) Serial.print("0");
  if (b < 16) shex+="0";
  //Serial.print(b, HEX);
  shex+=String(b,HEX);
  //Serial.print(" ");
  shex+=" ";
  return shex;
}




/********************************************************************************/
/*Function: sanswer. Returns a String answer from mp3 UART module.          */
/*Parameter:- uint8_t b. void.                                                  */
/*Return: String.  the answer (partial or full).                                */

 String sanswer(void)
{
  
  // start to read from mp3 serial.
  // if there are "0x7E" it's a beginning.
  //     iansbuf=0; //  ansbuf index to zero.
  //     ansbuf[iansbuf] = b;
  //     mp3answer=""; 
  //     // while there are something to read and it's not the end "0xEF"
  //
    // there are something and it is not a beginning.
    // if we are not in the middle of a message we have a problem.
      // we are in the middle of a message so let's continue.
      //  or at the beginning, anyway go for the reads.
      // if there are "0XEF" then we have a message.
   

  uint8_t b;
  
  // start to read from mp3 serial.
  b = mp3.read();
  
  // if there are "0x7E" it's a beginning.
  if(b == 0x7E)
   {
      iansbuf=0; //  ansbuf index to zero.
      ansbuf[iansbuf] = b;
      mp3answer="";
      // while there are something to read and it's not the end "0xEF"
   }
    else  // there are something and it is not a beginning.
   {
    // if we are not in the middle of a message we have a problem.
    if(iansbuf==0)
     {
       return "ERROR ";
     }
   }
      // we are in the middle of a message so let's continue.
      //  or at the beginning, anyway go for the reads.
     
      while (mp3.available() && ansbuf[iansbuf] != 0XEF)
      {
        iansbuf++; //  increase this index.
        ansbuf[iansbuf] = mp3.read();
        mp3answer+=sbyte2hex(ansbuf[iansbuf]);
        
      }
      // if there are "0XEF" then we have a message.
      if(ansbuf[iansbuf] == 0XEF)
      {      
         iansbuf=0;
         
      }       
     
  return mp3answer; 
 }
 
 
 
 





