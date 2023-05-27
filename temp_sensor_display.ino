

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

#pragma region 

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#pragma endregion

const char DEGREE_SYMBOL[] = {"\xb0"};

void setup(void) {
  sensors.begin();
  u8g2.begin();
}

void loop(void) {
  sensors.requestTemperatures(); // Send the command to get temperatures

  float currTemp = sensors.getTempFByIndex(0);

  u8g2.setFont(u8g2_font_ncenB14_tf);
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 20);
    u8g2.setDrawColor(2);

    u8g2.print(currTemp);
    u8g2.print(DEGREE_SYMBOL);
    u8g2.print("F");
  } while ( u8g2.nextPage() );

  delay(1000);
}

void lcdBold(bool aVal) {
  if (aVal) {
    u8g2.setFont(u8x8_font_saikyosansbold8_u);// BOLD
  } else {
    u8g2.setFont(u8g2_font_ncenB14_tr);// NORMAL
  }
}

