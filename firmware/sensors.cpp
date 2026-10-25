#include "sensors.h"
#include <Wire.h>

// Exponential Moving Average filter variables[cite: 8]
float ema_alpha = 0.2; 
float filtered_v_panel = 0.0;
float filtered_i_panel = 0.0;
float filtered_v_batt = 0.0;

void initSensors() {
    Wire.begin();
}

float getFilteredPanelVoltage() {
    float raw_val = 18.5; // Placeholder for INA226 read
    filtered_v_panel = (ema_alpha * raw_val) + ((1.0 - ema_alpha) * filtered_v_panel);
    return filtered_v_panel;
}

float getFilteredPanelCurrent() {
    float raw_val = 3.2; // Placeholder for INA226 read
    filtered_i_panel = (ema_alpha * raw_val) + ((1.0 - ema_alpha) * filtered_i_panel);
    return filtered_i_panel;
}

float getFilteredBatteryVoltage() {
    float raw_val = 12.1; // Placeholder for ADC read
    filtered_v_batt = (ema_alpha * raw_val) + ((1.0 - ema_alpha) * filtered_v_batt);
    return filtered_v_batt;
}

float getSystemTemperature() {
    return 35.0; // Placeholder for NTC thermistor read
}
