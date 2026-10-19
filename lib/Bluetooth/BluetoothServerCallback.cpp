#include "BluetoothServerCallback.h"

void BluetoothServerCallback::onConnect(BLEServer* pServer)
{
    Serial.println("Cliente Bluetooth conectado!");
}

void BluetoothServerCallback::onDisconnect(BLEServer* pServer)
{
    Serial.println("Cliente Bluetooth desconectado!");

    //Permite que outro dispositivo encontre o ESP32 novamente
    pServer->startAdvertising();
}