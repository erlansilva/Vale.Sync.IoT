#include "BluetoothCharacteristicCallback.h"

void BluetoothCharacteristicCallback::SaveValues(std::string json)
{
    JsonDocument doc;
    Serial.println(json.c_str());
    DeserializationError error = deserializeJson(doc, json);
    JsonObject obj = doc.as<JsonObject>();
    for (JsonPair kv : obj)
    {
        String key = kv.key().c_str(); // Obtém o nome da chave
        if (kv.value().is<bool>())
        {
            bool value = kv.value().as<bool>();
            Serial.printf("Chave: %s | Valor (bool): %d\n", key.c_str(), value);
        }
        else if (kv.value().is<const char *>())
        {
            const char *value = kv.value().as<const char *>();
            Serial.printf("Chave: %s | Valor (string): %s\n", key.c_str(), value);
        }
    }
}

void BluetoothCharacteristicCallback::onWrite(BLECharacteristic *pCharacteristic)
{
    std::string json = pCharacteristic->getValue();
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, json);

    if (error)
    {
        Serial.print("Falha ao ler o JSON: ");
        Serial.println(error.f_str());
        return;
    }
    int intType = doc["Type"];
    BluetoothMessageType type = static_cast<BluetoothMessageType>(intType);
    switch (type)
    {
        case BluetoothMessageType::Restart:
        {
            ESP.restart();
            break;
        }
        case BluetoothMessageType::Save:
        {
            std::string json;
            SaveValues(json);
            break;
        }
        case BluetoothMessageType::GetConfig: 
        {
            pCharacteristic->setValue("Dados atuais");
            pCharacteristic->notify();
            break;
        }
        default:
            {
                Serial.println("Erro no tipo de mensagem.");
                break;
            }
    }
}

void BluetoothCharacteristicCallback::CheckMessageType(std::string json)
{
    
}

BluetoothCharacteristicCallback::BluetoothCharacteristicCallback()
{
    _pre.begin(CONFIG_PREFERENCE_NAME, false);
}

BluetoothCharacteristicCallback::~BluetoothCharacteristicCallback()
{
}