/*
Simple library to use a BH1745NUC Digital Light Sensor.
SunFounder 2021
*/

#include "BH1745.h"

/**
 * Constructor
 */
BH1745::BH1745() {}

/**
 * Configure sensor
 */
#ifdef ESP32
bool BH1745::begin(int sda, int scl) {
  Wire.begin(sda, scl);
  return init();
}
#else
bool BH1745::begin() {
  Wire.begin();
  return init();
}
#endif

/**
 * Configure sensor
 */
bool BH1745::init() {
  Wire.beginTransmission(ADDR);
  Wire.write(CMD_SYSTEM_CONTROL);
  Wire.endTransmission();

  Wire.requestFrom(ADDR, 1);
  byte partNum = Wire.read();
  if (partNum != PART_NUMBER){
    return false;
  }

  Wire.beginTransmission(ADDR);
  Wire.write(CMD_MODE_CONTROL1);
  // 0x41
  Wire.write(MEASUREMENT_TIME_160);
  // 0x42
  Wire.write(RGBC_ENABLE + GAIN_16X);
  // 0x43
  Wire.write(0);
  // 0x44
  Wire.write(MODE_CONTROL3_DATA);
  // write8(CMD_SYSTEM_CONTROL, PART_NUMBER);
  // write8(CMD_MODE_CONTROL1, MEASUREMENT_TIME_160);
  // write8(CMD_MODE_CONTROL2, RGBC_ENABLE + GAIN_16X);
  // write8(CMD_MODE_CONTROL3, MODE_CONTROL3_DATA);
  Wire.endTransmission();
  return true;
}

/**
 *  Set gain of the internal ADC
 */
void BH1745::setGain(int gain){
  if(gain == GAIN_1X){
    write8(CMD_MODE_CONTROL2, RGBC_ENABLE + GAIN_1X);
  }else if(gain == GAIN_2X){
    write8(CMD_MODE_CONTROL2, RGBC_ENABLE + GAIN_2X);
  }else if(gain == GAIN_16X){
    write8(CMD_MODE_CONTROL2, RGBC_ENABLE + GAIN_16X);
  }else {
    #if DEBUG == 1
    Serial.println("Gain invalid, Try 'GAIN_1X/2/16X', like GAIN_2X");
    #endif
    return;
  }
}

/**
 *  Set RGBC Mode 8bit or 16bit
 */
void BH1745::setRgbcMode(int mode){
  if (mode != RGBC_8_BIT && mode != RGBC_16_BIT){
    #if DEBUG == 1
    Serial.println("RGBC Mode invalid, Try 'RGBC_8/16_BIT' like RGBC_8_BIT");
    #endif
  } else {
    rgbcMode = mode;
  }
}

/**
 * Read rgbc from sensor.
 * Returns -1 if read is timed out
 */
void BH1745::read() {
  Wire.beginTransmission(ADDR);
  Wire.write(RED_DATA_LSB);
  Wire.endTransmission();

  byte datas[8];
  Wire.requestFrom(ADDR, 8);
  int count = 0;
  while (Wire.available()) {
    byte c = Wire.read();
    datas[count] = c;
    count ++;
  }
  red = ((datas[1] << 8) + datas[0]) & 0xffff;
  green = ((datas[3] << 8) + datas[2]) & 0xffff;
  blue = ((datas[5] << 8) + datas[4]) & 0xffff;
  clear = ((datas[7] << 8) + datas[6]) & 0xffff;

  Serial.print("R: ");Serial.print(red, HEX);
  Serial.print(" G: ");Serial.print(green, HEX);
  Serial.print(" B: ");Serial.print(blue, HEX);
  Serial.print(" C: ");Serial.println(clear, HEX);
  if (rgbcMode == RGBC_8_BIT){
    red = red * 255 / 65535;
    green = green * 255 / 65535;
    blue = blue * 255 / 65535;
    clear = clear * 255 / 65535;
  }
}

void BH1745::write8(uint8_t cmd, uint8_t data) {
  Wire.beginTransmission(ADDR); 
  #if (ARDUINO >= 100)
    Wire.write(cmd); // Send register to write with CMD field
    Wire.write(data);  // Write data
  #else
    Wire.send(cmd); // Send register to write with CMD field
    Wire.send(data);  // Write data
  #endif
  Wire.endTransmission(); 
}
