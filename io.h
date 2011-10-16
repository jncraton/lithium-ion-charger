#ifndef IO_H
#define IO_H

#include <pic.h>

#define LED 0b00000001 //GP0
#define BAT_CON_A 0b00000100 //GP2
#define BAT_CON_B 0b00100000 //GP5

void toggleLED();
void enableChargeA();
void disableChargeA();
void enableChargeB();
void disableChargeB();

#endif