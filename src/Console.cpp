// Handles input for minicom serial
#include "Console.h"


String inputString(String Prompt){
    Serial.print(Prompt);
    String str = "";
    char c = 0;
    size_t len = 0;

    // Wait until serial port contains input
    while (Serial.available() == 0); 
    
    // Loop character by character until a newline or a carriage return is found
    while (c != '\n' && c != '\r')
    {   
        if (Serial.available() > 0) 
        {
            c = Serial.read();
            len = str.length();

            //Handle backspacing ( backspace and delete)
            if (len == 0 && (c == 8 || c == 127))
            {   
                c = 0;
                continue; 
            }
            if (c == 8 || c == 127)
            {
                
                str.remove(len-1);
                c = 8; // if char is del instead of backspace, treat it as a backspace
                Serial.print(c);
                Serial.print(' ');
                Serial.print(c);
                c = 0;
                continue;
            }

            // Limit acceptable characters to the following set
            if (c == '.' || c == ' ' || c == '-' ||
                (c >= 'a' && c <= 'z')||
                (c >= 'A' && c <= 'Z')||
                (c >= '0' && c <= '9')){
                Serial.print(c);
                str.concat(c);
                c = 0;
            } else
                continue;


        }
    }
    Serial.println("");
    return str;

}

int inputInt(String Prompt){
    Serial.print(Prompt);
    int result = 0xFFFFFFFF;
    char c = 0;
    String str = "";
    size_t len = 0;

    // Wait until serial port contains input
    while (Serial.available() == 0); 
    
    // Loop character by character until a newline or a carriage return is found
    while (c != '\n' && c != '\r')
    {   
        if (Serial.available() > 0) 
        {
            len = str.length();
            c = Serial.read();
            //Handle backspacing ( backspace and delete)
            if (len == 0 && (c == 8 || c == 127))
            {   
                c = 0;
                continue; 
            }
            if (c == 8 || c == 127)
            {
                str.remove(len-1);
                c = 8; // if char is del instead of backspace, treat it as a backspace
                Serial.print(c);
                Serial.print(' ');
                Serial.print(c);
                c = 0;
                continue;
            }

            // Limit acceptable characters to the following set
            if (c == '-' || (c >= '0' && c <= '9')){
                Serial.print(c);
                str.concat(c);
                c = 0;
            } else
                continue;


        }
    }
    Serial.println("");
    result = str.toInt();
    return result;

}


double inputDouble(String Prompt){
    Serial.print(Prompt);
    double result = 0xFFFFFFFF;
    char c = 0;
    String str = "";
    size_t len = 0;

    // Wait until serial port contains input
    while (Serial.available() == 0); 
    
    // Loop character by character until a newline or a carriage return is found
    while (c != '\n' && c != '\r')
    {   
        if (Serial.available() > 0) 
        {
            c = Serial.read();
            len = str.length();
            //Handle backspacing ( backspace and delete)
            if (len == 0 && (c == 8 || c == 127))
            {   
                c = 0;
                continue; 
            }
            if (c == 8 || c == 127)
            {
                str.remove(len-1);
                c = 8; // if char is del instead of backspace, treat it as a backspace
                Serial.print(c);
                Serial.print(' ');
                Serial.print(c);
                c = 0;
                continue;
            }

            // Limit acceptable characters to the following set
            if (c == '-' || c == '.' || (c >= '0' && c <= '9')){
                Serial.print(c);
                str.concat(c);
                c = 0;
            } else
                continue;


        }
    }
    Serial.println("");
    result = str.toDouble();
    return result;

}
