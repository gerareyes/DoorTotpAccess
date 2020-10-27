#include <Arduino.h>
#include "Keyboard.hpp"
#include "TimerController.hpp"
#include "CodeManager.hpp"

void setup()
{
    Serial.begin(9600);
    ConfigureTimer();
    SetCurrentTime();
}

void loop()
{
    UpdateTimer();

    if (MaxTimeReached())
    {
        ResetCode();
    }

    char key = GetKey();
    if (key)
    {
        ResetTimer();

        if (key == '#')
        {
            ResetCode();
        }
        else
        {
            AddToCode(key);
        }

        int result = ValidateCode();

        if (result == GATE_ENTRY)
        {
            Serial.println("Open entry gate");
        }
        else if (result == GATE_EXIT)
        {
            Serial.println("Open exit gate");
        }
    }
}