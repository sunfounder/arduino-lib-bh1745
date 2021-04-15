# Block design

Block design for Mixly

## begin

- Block Design: BH1745 begin SDA [pin] SCL [pin]
- Return: None
- Generator:
  - defination: `#include <BH1745.h>\nBH1745 bh = BH1745();`
  - code: `bh.begin(<sda>, <scl>);`

## read

- Block Design: BH1745 read
- Return: None
- Generator:
  - code: `bh.read();`

## Red/Green/Blue/Clear

- Block Design: BH1745 [Red/Green/Blue/Clear]
- Return: long
- Generator:
  - code: `bh.red/green/blue/clear;`

## Set RGBC Mode

- Block Design: BH1745 set RGBC mode [8 bit/16 bit]
- Return: None
- Generator:
  - code: `bh.setRgbcMode(bh.RGBC_8_BIT/bh.RGBC_16_BIT);`

## Set Gain

- Block Design: BH1745 set gain [1X/2X/16X]
- Return: None
- Generator:
  - code: `bh.setGain(bh.GAIN_1X/bh.GAIN_2X/bh.GAIN_16X);`
