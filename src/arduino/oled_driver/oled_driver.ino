/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 64 
#define LOGO16_GLCD_WIDTH  128 


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  

  // Clear the buffer.
  display.clearDisplay();

  

  
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("NAS DISP");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,40);
  display.println("BOOTING");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

  display.display();

delay(2000);
}

String readString;
String msg1 = "";
String msg2 = "";
int msg3 = 0; //HDD SPACE
int msg4 = 0; //RAM USAGE
bool fin = false;
void loop() {
    display.clearDisplay();

   while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      if(c == '\n'){
        Serial.println(readString);
        msg1 = "IP:" + getValue(readString, '_', 0);
    msg2 = getValue(readString, '_', 1);
    msg3 = getValue(readString, '_', 2).toInt();
     msg4 = getValue(readString, '_', 3).toInt();
    
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(msg1);
  display.setTextColor(BLACK, WHITE); // 'inverted' text



//HDD USAGE BAR
    // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println("DISK:" + msg2);
  display.setTextColor(BLACK, WHITE); // 'inverted' text

int bar_width = display.width()-5;
int bar_height = 10;
int rect_x = 0;
int rect_y = 25;
int percentage = msg3;

if(percentage < 0){percentage = 0;}
if(percentage > 100){percentage = 100;}
int inner_rect = percentage*((bar_width-4)/100);
 display.fillRect(rect_x,rect_y,bar_width, bar_height, 1);
 display.fillRect(rect_x+1,rect_y+1,bar_width-2, bar_height-2, 0);
display.fillRect(rect_x+2,rect_y+2,inner_rect, bar_height-4, 1);

display.display();


    // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,40);
  display.println("RAM USAGE");
  display.setTextColor(BLACK, WHITE); // 'inverted' text

//RAM USAGE BAR
rect_y = 50;
 percentage = msg4;
if(percentage < 0){percentage = 0;}
if(percentage > 100){percentage = 100;}
 inner_rect = percentage*((bar_width-4)/100);
 display.fillRect(rect_x,rect_y,bar_width, bar_height, 1);
 display.fillRect(rect_x+1,rect_y+1,bar_width-2, bar_height-2, 0);
display.fillRect(rect_x+2,rect_y+2,inner_rect, bar_height-4, 1);
display.display();

 readString="";}
    } 
  }

   if (readString.length() >0 && fin) {
    
   }
   
}




String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
