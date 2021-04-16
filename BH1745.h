/*
Simple library to use a BH1745NUC Digital Light Sensor.
SunFounder 2021
*/


#ifndef BH1745_h
#define BH1745_h

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define DEBUG 0

#define ADDR 0x39
#define PART_NUMBER 0x0B

#define CMD_SYSTEM_CONTROL 0x40
#define CMD_MODE_CONTROL1  0x41
#define CMD_MODE_CONTROL2  0x42
#define CMD_MODE_CONTROL3  0x44

#define RED_DATA_LSB   0x50
#define RED_DATA_MSB   0x51
#define GREEN_DATA_LSB 0x52
#define GREEN_DATA_MSB 0x53
#define BLUE_DATA_LSB  0x54
#define BLUE_DATA_MSB  0x55
#define CLEAR_DATA_LSB 0x56
#define CLEAR_DATA_MSB 0x57

#define MEASUREMENT_TIME_160  0x0
#define MEASUREMENT_TIME_320  0x1
#define MEASUREMENT_TIME_640  0x2
#define MEASUREMENT_TIME_1280 0x3
#define MEASUREMENT_TIME_2560 0x4
#define MEASUREMENT_TIME_5120 0x5

#define RGBC_ENABLE  0x10
#define RGBC_DISABLE 0x0

#define MODE_CONTROL3_DATA 0x02

class BH1745 {
  public:
    BH1745();

    int GAIN_1X  = 0x0;
    int GAIN_2X  = 0x1;
    int GAIN_16X = 0x2;
    int RGBC_16_BIT = 16;
    int RGBC_8_BIT  =  8;
    byte RED    = 0;
    byte ORANGE = 1;
    byte YELLOW = 2;
    byte GREEN  = 3;
    byte CYAN   = 4;
    byte BLUE   = 5;
    byte PURPLE = 6;
  
    #ifdef ESP32
    bool begin(int sda, int scl);
    #else
    bool begin();
    #endif
    void setGain(int gain);
    void setRgbcMode(int mode);
    void read();
    byte readColor();
    bool isDetectColor(byte color);
    long red = 0;
    long green = 0;
    long blue = 0;
    long clear = 0;
    long hue = 0;
    long saturation = 0;
    long lightness = 0;
    unsigned long rgb = 0;
    int rgbcMode = RGBC_8_BIT;


  private:
    void write8(uint8_t addr, uint8_t data);
    bool init();
    void rgb2hsv();
};

#endif
