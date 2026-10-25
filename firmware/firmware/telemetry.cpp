#include "telemetry.h"
#include <Arduino.h>

void initTelemetry() {
    // Initialize standard serial and optional Bluetooth Serial[cite: 12]
    Serial.println("Telemetry System Online");
}

void broadcastTelemetry(float v_in, float i_in, float v_batt, bool load_status) {
    Serial.print("PV_V: "); Serial.print(v_in);
    Serial.print(" | PV_I: "); Serial.print(i_in);
    Serial.print(" | BATT_V: "); Serial.print(v_batt);
    Serial.print(" | LOAD: "); Serial.println(load_status ? "ON" : "OFF");
}

void sendLog(const char* message) {
    Serial.println(message);
}
