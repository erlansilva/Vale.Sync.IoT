#pragma once
#include "Preferences.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "esp_bt_device.h"
#include "Constants/Defines.h"
#include "LocalStorage.h"
#include "ArduinoJson.h"
#include "Constants/BluetoothMessageType.h"

class BluetoothCharacteristicCallback : public BLECharacteristicCallbacks{
    private:
        Preferences _pre;
        void SaveValues(std::string json);
        void CheckMessageType(std::string json);
        

    public:
        BluetoothCharacteristicCallback();
        ~BluetoothCharacteristicCallback();
        void onWrite(BLECharacteristic *pCharacteristic) override;
        
};