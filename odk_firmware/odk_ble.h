#ifndef ODK_BLE
#define ODK_BLE

#define ODK_SERVICE_UUID        "b23cca98-2545-4842-a5af-0fc3550aadb0"
#define BATTERY_CHAR_UUID       "b23cca98-2545-4842-a5af-0fc3550aadb1"  // char[5]  e.g. "0.54"
#define GPS_LAT_CHAR_UUID       "b23cca98-2545-4842-a5af-0fc3550aadb2"  // char[8]  e.g. "-02.0452"
#define GPS_LON_CHAR_UUID       "b23cca98-2545-4842-a5af-0fc3550aadb3"  // char[9]  e.g. "+030.5415"
#define GPS_TIME_CHAR_UUID      "b23cca98-2545-4842-a5af-0fc3550aadb4"  // char[8]  e.g. "13:15:29"
#define GPS_DATE_CHAR_UUID      "b23cca98-2545-4842-a5af-0fc3550aadb5"  // char[10] e.g. "2025/09/17"
#define ANLG_CH0_UUID           "b23cca98-2545-4842-a5af-0fc3550aadb6"  // u16      e.g. 4096
#define ANLG_CH1_UUID           "b23cca98-2545-4842-a5af-0fc3550aadb7"  // u16      e.g. 1234

void ble_init();
void ble_poll();
int  ble_update_value(const char *uuid, byte *buf, size_t len);

#endif