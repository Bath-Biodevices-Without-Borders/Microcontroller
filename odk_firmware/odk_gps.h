#ifndef ODK_GPS
#define ODK_GPS

#include "TinyGPSPlus.h"
#include "SoftwareSerial.h"

void gps_init();
void gps_poll(bool force = false);
int gps_command(char cmd);

#endif