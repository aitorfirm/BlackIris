#ifndef SYRIAL_SHARED_LOGGER_H
#define SYRIAL_SHARED_LOGGER_H

#include <Uefi.h>

VOID InitLogger(BOOLEAN EnableVerbose);
VOID LogInfo(CONST CHAR16* Msg);
VOID LogWarn(CONST CHAR16* Msg);
VOID LogError(CONST CHAR16* Msg);
VOID LogRaw(CONST CHAR16* Msg);

#endif 
