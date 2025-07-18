#include "RemoteControl.h"
#include "CommandExec.h"
#include "../Shared/Logger.h"
#include "../Shared/MemTools.h"

#define SHARED_CMD_BUFFER_PHYS 0x90000  // set this up
#define MAX_CMD_LEN 256

static CHAR16 LastCmd[MAX_CMD_LEN] = {0};

BOOLEAN InitRemoteControl(void) {
    LogInfo(L"Started successfully\n");
    return TRUE;
}

VOID RemotePoll(void) {
    CHAR16* CmdPtr = (CHAR16*)PhysToVirt(SHARED_CMD_BUFFER_PHYS);
    if (!CmdPtr) return;

    if (StrLen(CmdPtr) == 0 || StrCmp(CmdPtr, LastCmd) == 0)
        return;

    StrCpy(LastCmd, CmdPtr);  
    LogInfo(L"command received: ");
    LogInfo(CmdPtr);

    ProcessCommand(CmdPtr);
}
