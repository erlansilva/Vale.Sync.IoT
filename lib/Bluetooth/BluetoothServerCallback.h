#pragma once

#include <BLEServer.h>
#include "Arduino.h"
class BluetoothServerCallback : public BLEServerCallbacks
{
    public:
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;
};