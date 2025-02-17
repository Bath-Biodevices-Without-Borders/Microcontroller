#ifndef ODK_TEMP_SENSOR
#define ODK_TEMP_SENSOR

#define DS18S20_PIN 3

#include <OneWire.h>

float get_temp();

#endif