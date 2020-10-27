#include "sha1.h"
#include "TOTP.h"
#include "TimerController.hpp"

uint8_t hmacEntryGateKey[] = {0x74, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67};
uint8_t hmacExitGateKey[] = {0x74, 0x65, 0x73, 0x74, 0x69, 0x6e, 0x67};

TOTP totpEntryGate = TOTP(hmacEntryGateKey, 7);
TOTP totpExitGate = TOTP(hmacExitGateKey, 7);

String typedCode = "";
int codeLength = 6;

int GATE_ENTRY = 1;
int GATE_EXIT = 2;

void AddToCode(char val)
{
    typedCode += val;
}

void ResetCode()
{
    Serial.println("Reset Code");
    typedCode = "";
}

bool IsValidCode(TOTP topt, String code)
{
    long GMT = GetTimestamp();
    char *validCode = topt.getCode(GMT);
    Serial.print("Typed totp: ");
    Serial.print(code);
    Serial.print(" - Original topt: ");
    Serial.println(validCode);
    return strcmp(validCode, code.c_str()) == 0;
}

int ValidateCode()
{
    int result = 0;
    if (typedCode.length() >= codeLength)
    {
        if (IsValidCode(totpEntryGate, typedCode))
        {
            Serial.println("Entry code valid");
            result = GATE_ENTRY;
        }
        else if (IsValidCode(totpExitGate, typedCode))
        {
            Serial.println("Exit code valid");
            result = GATE_EXIT;
        }

        ResetCode();
    }

    return result;
}