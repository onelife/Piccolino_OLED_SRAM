// For the OLED, we need I2C
#include <Wire.h>

// For the FRAM we need SPI
#include <SPI.h>

// I2C OLED library
#include <Piccolino_OLED_SRAM.h>
#include <Piccolino_RAM.h>

// SPI SD card
#include <SdFat.h>

Piccolino_OLED_SRAM display; // our OLED object ...


void setup() {
  Serial.begin(9600);
  display.begin();

  display.clear();
  display.setCursor(0,16); // skip yellow portion of display
   
  display.setTextColor(WHITE);
  if (!display.setFont(HZK_16, "hzk16font.fnt")) {
    Serial.println("setFont error");
  }
  display.print("\xd4\xcf\xbe\xca\xba\xba\xd6\xd7\n");
  if (!display.setFont(ASCII_16, "ascii16font.fnt")) {
    Serial.println("setFont error");
  }
  display.print("123, ABC, abc\n");
  display.update();
}


void loop () {
}
