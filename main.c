#include <pic.h>

#include "io.h"

// Configure for internal oscillator at 4 MHz
__CONFIG (INTIO & BORDIS & OSC_4MHZ & UNPROTECT & MCLREN & PWRTDIS & WDTDIS);

// Set voltage to charge to
// 209 = (4.1/5.0) * 255
// Stop charging at 4.1 volts
#define V_CUTOFF 209

unsigned char getVoltage() {
    for(char i = 0; i < 255; i++);
    ADCON0 |= 0b00000010; // Start conversion
    while(ADCON0 & 0b00000010); // Wait for conversion
    unsigned char voltage = ADRESH;
    if(voltage > V_CUTOFF) voltage = V_CUTOFF;
    if(voltage < 120) voltage = V_CUTOFF; // Return high value if no battery present
    return voltage;
}

unsigned char getVoltageA() {
    ADCON0 = 0b00000101; // Start the ADC on AN1
    return getVoltage();
}

unsigned char getVoltageB() {
    ADCON0 = 0b00001101; // Start the ADC on AN3
    return getVoltage();
}

void init() {
    CCP1CON = 0b00000000; // Disable Comparater and PWM
    TRISIO = ~(LED|BAT_CON_A|BAT_CON_B);
    ANSEL = ~(LED|BAT_CON_A|BAT_CON_B);

    disableChargeA();
    disableChargeB();
}

void main() {
    init();

    while(1) {
        unsigned char voltageA = getVoltageA();
        unsigned char voltageB = getVoltageB();
        unsigned char delay = (V_CUTOFF - voltageA) + (V_CUTOFF - voltageB);

        for(unsigned char i = 0; i < delay; i++) {
            for(unsigned char j = 0; j < 255; j++);
        }
        
        toggleLED();

        if(voltageA >= V_CUTOFF) disableChargeA();
        if(voltageA <= V_CUTOFF-10) enableChargeA(); // Disable charging ~.2V below cutoff

        if(voltageB >= V_CUTOFF) disableChargeB();
        if(voltageB <= V_CUTOFF-10) enableChargeB(); // Disable charging ~.2V below cutoff
    }
}
