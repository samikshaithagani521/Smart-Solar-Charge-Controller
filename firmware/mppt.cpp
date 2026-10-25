#include "mppt.h"
#include <math.h>

float prev_v = 0.0;
float prev_p = 0.0;
int current_duty = 128; 

// Advanced tracking with variable step size[cite: 8]
int runAdvancedMPPT(float v_panel, float i_panel) {
    float current_p = v_panel * i_panel;
    float delta_p = current_p - prev_p;
    float delta_v = v_panel - prev_v;
    
    // Variable step calculation: larger step if far from MPP, small step if close[cite: 8]
    int step_size = (abs(delta_p) > 5.0) ? 5 : 1; 

    if (delta_p != 0) {
        if (delta_p > 0) {
            if (delta_v > 0) {
                current_duty -= step_size;
            } else {
                current_duty += step_size;
            }
        } else {
            if (delta_v > 0) {
                current_duty += step_size;
            } else {
                current_duty -= step_size;
            }
        }
    }
    
    // Clamp duty cycle to hardware limits
    if (current_duty > 230) current_duty = 230;
    if (current_duty < 25) current_duty = 25;
    
    prev_v = v_panel;
    prev_p = current_p;
    
    return current_duty;
}
