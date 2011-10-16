#include "adc.h"

unsigned char getVoltageA() {
    ADCON0 = 0b00000101; // Configure the ADC on AN1
    return getVoltage();
}

unsigned char getVoltageB() {
    ADCON0 = 0b00001101; // Configure the ADC on AN3
    return getVoltage();
}

unsigned char getVoltage() {
    // Delay for a short time
    for(char i = 0; i < 255; i++);

    // Start conversion
    ADCON0 |= 0b00000010; 

    // Wait for conversion
    while(ADCON0 & 0b00000010);

    // Grab the voltage
    unsigned char voltage = ADRESH;

    // Adjust the value as needed
    if(voltage > V_CUTOFF) voltage = V_CUTOFF; // Don't exceed V_CUTOFF
    if(voltage < 120) voltage = V_CUTOFF; // Return high value if no battery

    return voltage;
}