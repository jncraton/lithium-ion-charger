#include "adc.h"

unsigned char getVoltageA() {
    ADCON0 = 0b00000101; // Start the ADC on AN1
    return getVoltage();
}

unsigned char getVoltageB() {
    ADCON0 = 0b00001101; // Start the ADC on AN3
    return getVoltage();
}

unsigned char getVoltage() {
    for(char i = 0; i < 255; i++);
    ADCON0 |= 0b00000010; // Start conversion
    while(ADCON0 & 0b00000010); // Wait for conversion
    unsigned char voltage = ADRESH;
    if(voltage > V_CUTOFF) voltage = V_CUTOFF;
    if(voltage < 120) voltage = V_CUTOFF; // Return high value if no battery present
    return voltage;
}