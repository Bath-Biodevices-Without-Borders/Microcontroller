#include <Arduino.h>
#include <ArduinoBLE.h>
#include <stdint.h>
#include "odk_ble.h"


// Characteristics and Services ------------------------------------------------
// Create BLE Service
BLEService odkService(ODK_SERVICE_UUID);

// Create BLE Characteristics
BLECharacteristic batChstic(BATTERY_CHAR_UUID, BLERead, "0.50");            // Battery Percentage
BLECharacteristic gpsLatChstic(GPS_LAT_CHAR_UUID, BLERead, "+00.0000");     // GPS Latitude
BLECharacteristic gpsLonChstic(GPS_LON_CHAR_UUID, BLERead, "+000.0000");    // GPS Longitude
BLECharacteristic gpsTimeChstic(GPS_TIME_CHAR_UUID, BLERead, "00:00:00");   // GPS Time
BLECharacteristic gpsDateChstic(GPS_DATE_CHAR_UUID, BLERead, "2000/01/01"); // GPS Date
BLECharacteristic anlgCh0Chstic(ANLG_CH0_UUID, BLERead, "9999");       // Analogue channel 0
BLECharacteristic anlgCh1Chstic(ANLG_CH1_UUID, BLERead, "9999");       // Analogue channel 1
// -----------------------------------------------------------------------------

// Callback handlers -----------------------------------------------------------
// Connection made callback
void blePeripheralConnectHandler(BLEDevice central) {
    // central connected event handler
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
    BLE.stopAdvertise();
}

// Connection dropped callback
void blePeripheralDisconnectHandler(BLEDevice central) {
    // central disconnected event handler
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
}
// -----------------------------------------------------------------------------

// Functions -------------------------------------------------------------------
void ble_init()
{
    if (!BLE.begin()) {
    	Serial.println("Starting BLE module failed!");
    	while (1);
    }

    BLE.setLocalName("ODK - Oasis Development Kit");
    // Add service and set the UUID for the service this peripheral advertises

    // Add the characteristics to the service
    odkService.addCharacteristic(batChstic);
    odkService.addCharacteristic(gpsLatChstic);
    odkService.addCharacteristic(gpsLonChstic);
    odkService.addCharacteristic(gpsTimeChstic);
    odkService.addCharacteristic(gpsDateChstic);
    odkService.addCharacteristic(anlgCh0Chstic);
    odkService.addCharacteristic(anlgCh1Chstic);

    BLE.addService(odkService);
    BLE.setAdvertisedService(odkService);
    
    // Attach event handlers for connection/disconnection to peripheral
    BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
    BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

    
    // Start advertising to nearby devices
    BLE.advertise();


    Serial.println("BLE device active, waiting for connections...");
}

void ble_poll()
{
    BLE.poll();
}

int ble_update_value(const char *uuid, byte *buf, size_t len)
{
    BLECharacteristic thisChar = odkService.characteristic(uuid);
    // if (thisChar.valueLength() != len)
    // {
    //     Serial.printf("len (%d) does not match characteristic size (%d) - skipping\n",len, thisChar.valueLength());
    //     return 0;
    // }
    return thisChar.writeValue(buf,len);
}
// -----------------------------------------------------------------------------