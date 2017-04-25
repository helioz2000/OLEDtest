/*
 * Test for OLED display
 * requires U8g2 library by oliver
 * https://github.com/olikraus/u8g2/wiki/
 */

#include <Arduino.h>
#include <SPI.h>
#include <U8x8lib.h>

/* Constructor */
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* clock=*/ 21, /* data=*/ 20);
/* u8x8.begin() is required and will sent the setup/init sequence to the display */

uint8_t contrast;
bool dir;

void setup(void)
{
  Serial.begin(9600); 
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0," OLED by VK3ERW ");
  //u8x8.drawString(0,1,"1:");
  //u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  //u8x8.setFont(u8x8_font_5x7_r);
  //u8x8.setFont(u8x8_font_5x8_r);
  //u8x8.setFont( u8x8_font_artossans8_r );
  //u8x8.setFont( u8x8_font_victoriabold8_r );
  //u8x8.setFont( u8x8_font_pressstart2p_r );
  //u8x8.drawString(0,2,"2: Hello World");
  //u8x8.setInverseFont(1);
  //u8x8.drawString(0,3,"0123456789012345");
  contrast = 255;
  dir = false;
  u8x8.drawString(0,2,"Contrast:");
}

void loop(void)
{
  u8x8.setContrast(contrast);
  u8x8.setCursor(10,2);
  u8x8.print ("   ");
  u8x8.setCursor(10,2);
  u8x8.print(contrast);
  //Serial.print("Contrast: ");
  //Serial.println(contrast);

  //delay(2000);
  //u8x8.setPowerSave(1);
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

  //u8x8.setPowerSave(0);
}
