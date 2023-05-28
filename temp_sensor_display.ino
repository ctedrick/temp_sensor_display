

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
DallasTemperature tempSensor(&oneWire);

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

#pragma endregion

DeviceAddress thermometerAddress;
const char DEGREE_SYMBOL[] = { "\xb0" };

void setup(void) {
  Serial.begin(9600);
  tempSensor.begin();

  u8g2.begin();

  if (!tempSensor.getAddress(thermometerAddress, 0)) {
    Serial.println("Device not found!");
  } else {
    Serial.println("Device 0 Address: ");
    // printAddress(thermometerAddress);
  }

  tempSensor.setResolution(thermometerAddress);

    u8g2.setDrawColor(2);
}

void loop(void) {
  tempSensor.requestTemperatures();  // Send the command to get temperatures

  // float currTemp = tempSensor.getTempFByIndex(0);
  int currTemp = 69;

  u8g2.firstPage();
  do {
    centerText(u8g2_font_squeezed_b7_tr, "Engine Temp - Fahrenheit", 8);

    char currTempString[8];
    itoa(currTemp, currTempString, 10);
    centerText(u8g2_font_crox4hb_tf, currTempString, 40);

  } while (u8g2.nextPage());

  delay(1000);
}

void centerText(const uint8_t* font, const char* value, int y) {
  u8g2.setFont(font);

  float sW = u8g2.getStrWidth(value);
  float dX = u8g2.getDisplayWidth();

  float finalX = (dX - sW) * 0.5;

  u8g2.setCursor(finalX, y);
  u8g2.println(value);
}
