#include "Bluetooth.h"

void Bluetooth::Init()
{
    uint8_t mac[6];

    esp_read_mac(mac, ESP_MAC_BT);

    char bluetoothName[40];

    snprintf(
        bluetoothName,
        sizeof(bluetoothName),
        "Vale Sync Es32 - %02X%02X%02X",
        mac[3],
        mac[4],
        mac[5]);

    // Inicializa BLE
    BLEDevice::init(bluetoothName);

    // Server
    BLEServer *pServer = BLEDevice::createServer();

    // Service
    BLEService *pService = pServer->createService(
        SERVICE_UUID);

    // Characteristic
    BLECharacteristic *pCharacteristic =
        pService->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
                BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setValue("Vale Sync");
    pCharacteristic->setCallbacks(new BluetoothCallBack());
    // Inicia service
    pService->start();

    // Advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

    pAdvertising->addServiceUUID(SERVICE_UUID);

    pAdvertising->setScanResponse(true);

    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();

    Serial.println("BLE iniciado!");
    Serial.printf("Nome: %s\n", bluetoothName);
    Serial.println("Aguardando conexão...");
}

Bluetooth::Bluetooth()
{
}

Bluetooth::~Bluetooth() {}