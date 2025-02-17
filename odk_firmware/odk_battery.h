#ifndef ODK_BATTERY
#define ODK_BATTERY

#include "Wire.h"

#define MAX17049G_ADR (0b0110110)

#define BAT_VCELL           (0x02)  // Battery Voltage Register         R
#define BAT_SOC             (0x04)  // State of Charge Register         R
#define BAT_MODE            (0x06)  // Mode Register                      W
#define BAT_VERSION         (0x08)  // Version Register                 R
#define BAT_HIBRT           (0x0A)  // Hibernate Threshold              R W
#define BAT_CONFIG          (0x0C)  // Configuration Register           R W
#define BAT_VALERT          (0X14)  // VCELL alert threshold            R W
#define BAT_CRATE           (0x16)  // Approx charge rate               R
#define BAT_VRESETID        (0x18)  // Reset VCEKK thresold             R W
#define BAT_STATUS          (0x1A)  // Status reg                       R W
// ...
#define BAT_TABLE           (0xFE)  // Send POR command                 R W

void wire_init()
{
    Wire.begin();
}

uint16_t read_bat_reg(uint8_t adr)
{
    Wire.beginTransmission(MAX17049G_ADR);
    Wire.write(byte(adr)); //send register address to read
    Wire.endTransmission(false);

    Wire.requestFrom(MAX17049G_ADR, 2, 1);
    while (Wire.available() != 2);

    uint16_t retval = ((uint16_t)Wire.read()) << 8 | ((uint16_t)Wire.read());
    return retval;
}

void write_bat_reg(uint8_t adr, uint16_t data)
{
    Wire.beginTransmission(MAX17049G_ADR);
    Wire.write(byte(adr));         // Send register address to write
    Wire.write((uint8_t)(data >> 8)); // Send the high byte of the data
    Wire.write((uint8_t)(data & 0xFF)); // Send the low byte of the data
    Wire.endTransmission();       // Complete the transmission
}


#endif