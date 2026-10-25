#ifndef SENSORS_H
#define SENSORS_H
void initSensors();
float getFilteredPanelVoltage();
float getFilteredPanelCurrent();
float getFilteredBatteryVoltage();
float getSystemTemperature();
#endif
