/*
 * Test for OLED display
 * requires U8g2 library by oliver
 * https://github.com/olikraus/u8g2/wiki/
 * 
 * Connection:
 * OLED -> Arduino Nano
 * GND -> GND
 * VCC -> 5V
 * SCL -> A5
 * SDA -> A4
 */

// We can run two modes, text or graphics. 
// Comment out the line below for graphics mode
#define TEXTMODE

#include <Arduino.h>
#include <SPI.h>

#ifdef TEXTMODE
#include <U8x8lib.h>
/* Constructor for text mode */
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* clock=*/ 21, /* data=*/ 20);
#else
#include <U8g2lib.h>
/* Constructor for graphic mode */
U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(/* rotation=*/ U8G2_R0, /* clock=*/ 21, /* data=*/ 20);
#endif

uint8_t contrast;
bool dir;

void setup(void)
{
  Serial.begin(9600);
#ifdef TEXTMODE
  u8x8.begin(); /* u8x8.begin() is required and will sent the setup/init sequence to the display */
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0," OLED by VK3ERW ");
  u8x8.drawString(0,1,"1: Hello World");
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.setFont(u8x8_font_5x7_r);
  u8x8.setFont(u8x8_font_5x8_r);
  u8x8.setFont( u8x8_font_artossans8_r );
  u8x8.setFont( u8x8_font_victoriabold8_r );
  u8x8.setFont( u8x8_font_pressstart2p_r );
  //u8x8.drawString(0,2,"2: Hello World");
  //u8x8.setInverseFont(1);
  u8x8.drawString(0,3,"0123456789012345");
  u8x8.drawString(0,2,"Contrast:");
#else
  u8g2.begin();
#endif
  contrast = 255;
  dir = false;
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

}

void loop(void)
{
#ifdef TEXTMODE
  u8x8.setContrast(contrast);
  u8x8.setCursor(10,2);
  u8x8.print ("   ");
  u8x8.setCursor(10,2);
  u8x8.print(contrast);
  Serial.print("Contrast: ");
  Serial.println(contrast);
  delay(200);
  //u8x8.setPowerSave(1);
#endif
  delay(80);
  if (dir == false) {
    if (contrast > 0) {
      contrast -= 5;
    } else {
      dir = true;
      delay(2000);
    }
  } else {
    if (contrast < 255) {
      contrast += 5;
    } else {
      dir = false;
      delay(2000);
    }
  }
  
#ifndef TEXTMODE
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(20,28,"VK3ERW");
  } while ( u8g2.nextPage() );
#endif

#ifdef TEXTMODE
  //u8x8.setPowerSave(0);
#endif
}
