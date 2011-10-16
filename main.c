#include <pic.h>

#include "io.h"
#include "adc.h"

// Configure for internal oscillator at 4 MHz
__CONFIG (INTIO & BORDIS & OSC_4MHZ & UNPROTECT & MCLREN & PWRTDIS & WDTDIS);

void init() {
    // Disable Comparater and PWM
    CCP1CON = 0b00000000;

    // Set port direction
    TRISIO = ~(LED|BAT_CON_A|BAT_CON_B);

    // Enable analog pins
    ANSEL = ~(LED|BAT_CON_A|BAT_CON_B);

    // Disable charging initially
    disableChargeA();
    disableChargeB();
}

void main() {
    init();

    while(1) {
        // Grab the current battery charge level
        unsigned char voltageA = getVoltageA();
        unsigned char voltageB = getVoltageB();

        // Delay based on the current charge levels
        unsigned char delay = (V_CUTOFF - voltageA) + (V_CUTOFF - voltageB);
        for(unsigned char i = 0; i < delay; i++) {
            for(unsigned char j = 0; j < 255; j++);
        }
        
        toggleLED();

        // Logic to determine if we should charge or not
        if(voltageA >= V_CUTOFF) disableChargeA();
        if(voltageA <= V_CUTOFF-10) enableChargeA();

        if(voltageB >= V_CUTOFF) disableChargeB();
        if(voltageB <= V_CUTOFF-10) enableChargeB();
    }
}
