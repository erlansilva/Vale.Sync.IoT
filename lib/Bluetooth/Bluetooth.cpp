#include "Bluetooth.h"

void Bluetooth::Init()
{
    // Garanta que os ponteiros não são NULL antes de registrar nos callbacks
    if (_serverCallback == nullptr) _serverCallback = new BluetoothServerCallback();
    if (_charCallback == nullptr) _charCallback = new BluetoothCharacteristicCallback();
    uint8_t mac[6];

    esp_read_mac(mac, ESP_MAC_BT);

    char bluetoothName[40];

    snprintf(
        bluetoothName,
        sizeof(bluetoothName),
        "Vale Sync Esp32 - %02X%02X%02X",
        mac[3],
        mac[4],
        mac[5]);

    // Inicializa BLE
    BLEDevice::init(bluetoothName);

    BLEDevice::setMTU(512);

    // Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(_serverCallback);
    

    // Service
    BLEService *pService = pServer->createService(
        SERVICE_UUID);

    // Characteristic
    pCharacteristic = pService->createCharacteristic(
            RX_CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic->setCallbacks(_charCallback);
    pCharacteristic->addDescriptor(new BLE2902());
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
    int countSend = 0;
    while (true)
    {
    }
    
}

Bluetooth::Bluetooth()
{
    _serverCallback = new BluetoothServerCallback();
    _charCallback = new BluetoothCharacteristicCallback();
}

Bluetooth::~Bluetooth() {
    delete _serverCallback;
    delete _charCallback;
}

void Bluetooth::SendMessage(const std::string& message){
    if (pCharacteristic == nullptr)
        return;

    pCharacteristic->setValue(message);
    pCharacteristic->notify();
}