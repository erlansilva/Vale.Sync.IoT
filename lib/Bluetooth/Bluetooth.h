#ifndef ARDUINO_LIB
#define ARDUINO_LIB
#include "Arduino.h"
#endif

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "LocalStorage.h"
#include "esp_bt_device.h"
#include "Preferences.h"
#include "Constants/Defines.h"
#include "ArduinoJson.h"
#include "string.h"

class Bluetooth
{
public:
    Bluetooth();
    ~Bluetooth();
    void Init();

private:
};

class BluetoothCallBack : public BLECharacteristicCallbacks
{
private:
    Preferences _pre;

    void SaveValues(String json)
    {
        JsonDocument doc;

        DeserializationError error = deserializeJson(doc, json);

        if (error)
        {
            Serial.print("Falha ao ler o JSON: ");
            Serial.println(error.f_str());
            return;
        }

        JsonObject obj = doc.as<JsonObject>();

        for(JsonPair kv : obj){
            String key = kv.key().c_str();  // Obtém o nome da chave
            if(kv.value().is<bool>())
            {
                bool value = kv.value().as<bool>();
                Serial.printf("Chave: %s | Valor (bool): %d\n", key.c_str(), value);
            }
            else if(kv.value().is<const char*>())
            {
                const char* value = kv.value().as<const char*>();
                Serial.printf("Chave: %s | Valor (string): %s\n", key.c_str(), value);
            }
        }
    }

protected:
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();
        String message = String(value.c_str());
        Serial.println(message);
        //SaveValues(message);
        // _pre.putString(WIFI_PREFERENCE_NAME, "");
        // delay(2000);
    }

public:
    BluetoothCallBack()
    {
        _pre.begin(CONFIG_PREFERENCE_NAME, false);
    }
};