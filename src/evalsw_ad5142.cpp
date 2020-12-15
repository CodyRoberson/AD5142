#include <Arduino.h>
#include "Console.h"
#include "AD5142.h"

// *********** SET SPI LATCH EN PIN HERE ERIC/ME **********
#define LE 10
// ********************************************************

AD5142 *dev;

void setup() {
    Serial.begin(9600);
    SPI.begin();
    pinMode(LE, OUTPUT);
    digitalWrite(LE, HIGH);
    dev = new AD5142(&SPI, LE);
}

void loop() {

}