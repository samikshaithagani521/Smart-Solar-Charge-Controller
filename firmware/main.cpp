#include <Arduino.h>
#include "sensors.h"
#include "mppt.h"
#include "telemetry.h"

const int pwmPin = 18;
const int loadDisconnectPin = 19; 
const int pwmFreq = 50000; 
const int pwmChannel = 0;
const int pwmResolution = 8;

// Safety Thresholds[cite: 5, 14]
const float BATT_MAX_VOLTAGE = 14.4; 
const float BATT_LVD_DISCONNECT = 11.2; 
const float BATT_LVD_RECONNECT = 12.6;
const float MAX_TEMP_C = 65.0;

bool loadEnabled = true;

void setup() {
    Serial.begin(115200);
    initSensors();
    initTelemetry();
    
    pinMode(loadDisconnectPin, OUTPUT);
    digitalWrite(loadDisconnectPin, HIGH); // Enable load
    
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(pwmPin, pwmChannel);
}

void loop() {
    // 1. Read Filtered Sensors[cite: 8]
    float v_panel = getFilteredPanelVoltage();
    float i_panel = getFilteredPanelCurrent();
    float v_batt = getFilteredBatteryVoltage();
    float temp = getSystemTemperature();
    
    // 2. Safety Fault Protection & Load Control[cite: 5]
    if (temp > MAX_TEMP_C) {
        ledcWrite(pwmChannel, 0); // Thermal shutdown
        sendLog("FAULT: Overtemperature");
        return;
    }
    
    if (v_batt > BATT_MAX_VOLTAGE) {
        ledcWrite(pwmChannel, 0); // Stop charging
        sendLog("STATUS: Battery Full");
    } else {
        // Run Advanced MPPT[cite: 8]
        int new_pwm_duty = runAdvancedMPPT(v_panel, i_panel);
        ledcWrite(pwmChannel, new_pwm_duty);
    }
    
    // Low Voltage Disconnect (LVD)[cite: 5, 14]
    if (v_batt < BATT_LVD_DISCONNECT && loadEnabled) {
        digitalWrite(loadDisconnectPin, LOW);
        loadEnabled = false;
        sendLog("FAULT: LVD Active. Load disconnected.");
    } else if (v_batt > BATT_LVD_RECONNECT && !loadEnabled) {
        digitalWrite(loadDisconnectPin, HIGH);
        loadEnabled = true;
        sendLog("STATUS: LVD Cleared. Load reconnected.");
    }
    
    // 3. Transmit Telemetry[cite: 12]
    broadcastTelemetry(v_panel, i_panel, v_batt, loadEnabled);
    
    delay(100); 
}
