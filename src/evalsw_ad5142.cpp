#include <Arduino.h>
#include "Console.h"
#include "AD5142.h"

// *********** SET SPI LATCH EN PIN HERE ERIC/ME **********
#define LE 7
// ********************************************************

AD5142 *dev;

void setup() {
    Serial.begin(9600);
    SPI.begin();
    pinMode(LE, OUTPUT);
    digitalWrite(LE, HIGH);
    delayMicroseconds(500);
    dev = new AD5142(&SPI, LE);
}

void printMenu()
{
    Serial.println("\r\nSelect from the following options:");
    Serial.print("1. Set wiper 1 Resistance, currently at ");
        Serial.println(dev->getWiper1());
    Serial.print("2. Set wiper 2 Resistance, currently at ");
        Serial.println(dev->getWiper2());
}

void loop() {
    int inpt, resistance;

    printMenu();
    inpt = inputInt("OPTION> ");

    if (inpt == 1)
    {
        resistance = inputInt("wiper 1 resistance: ");
        dev->setResistance(1, resistance);
    } else if (inpt == 2){
        resistance = inputInt("wiper 2 resistance: ");
        dev->setResistance(2, resistance);
    }
    
    
}