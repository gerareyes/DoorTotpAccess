#include "sha1.h"
#include "TOTP.h"
#include "TimerController.hpp"

extern int GATE_ENTRY;
extern int GATE_EXIT;

bool IsValidCode();
void AddToCode(char val);
void ResetCode();
int ValidateCode();