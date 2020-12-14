#include <Arduino.h>
#ifndef __CONSOLE_IO__
#define __CONSOLE_IO__

/**
 * @brief Displays the given prompt, then returns a string
 * 
 * @param Prompt 
 * @return String 
 */
String inputString(String Prompt);

/**
 * @brief Displays the given prompt, then returns an integer
 * 
 * @param Prompt 
 * @return int 
 */
int inputInt(String Prompt);

/**
 * @brief Displays the given prompt, then returns a decimal number
 * 
 * @param Prompt 
 * @return double 
 */
double inputDouble(String Prompt);

#endif