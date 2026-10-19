#pragma once
#include "Arduino.h"
#include "BluetoothCharacteristicCallback.h"
#include "BluetoothServerCallback.h"
#include <BLE2902.h>

class Bluetooth
{
    public:
        Bluetooth();
        ~Bluetooth();
        void Init();
        void SendMessage(const std::string& message);

    private:
        BluetoothServerCallback* _serverCallback;
        BluetoothCharacteristicCallback* _charCallback;
        BLECharacteristic *pCharacteristic;
};