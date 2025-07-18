#include "Loader.h"
#include "DXEHook.h"
#include "BootkitDefs.h"
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

EFI_STATUS InitializeBootkit(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
    EFI_STATUS Status;

    gST = SystemTable;
    gBS = SystemTable->BootServices;
    gRT = SystemTable->RuntimeServices;

    Status = InstallExitBootServicesHook();
    if (EFI_ERROR(Status)) {
        return Status;
    }

    return EFI_SUCCESS;
}
