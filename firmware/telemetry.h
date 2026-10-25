#ifndef TELEMETRY_H
#define TELEMETRY_H
void initTelemetry();
void broadcastTelemetry(float v_in, float i_in, float v_batt, bool load_status);
void sendLog(const char* message);
#endif
