#include <Arduino.h>
// put function declarations here:
#include "Bluetooth.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Teste");
    Bluetooth ble;
    ble.Init();    
}

void loop() {
  
}

// put function definitions here:
