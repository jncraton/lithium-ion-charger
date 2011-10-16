#include "io.h"

void toggleLED() {
    GPIO ^= LED;
}

void enableChargeA() {
    // A low value enables charging
    GPIO = GPIO & ~BAT_CON_A;
}

void disableChargeA() {
    // A high value disables charging
    GPIO |= BAT_CON_A;
}

void enableChargeB() {
    // A low value enables charging
    GPIO = GPIO & ~BAT_CON_B;
}

void disableChargeB() {
    // A high value disables charging
    GPIO |= BAT_CON_B;
}
