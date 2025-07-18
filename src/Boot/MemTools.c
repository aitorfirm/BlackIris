#include "MemTools.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

VOID* MmMapIoSpace(IN EFI_PHYSICAL_ADDRESS PhysAddr, IN UINTN Length, IN BOOLEAN Write) {
    EFI_STATUS Status;
    VOID* VirtualAddr = NULL;

    Status = gBS->AllocatePages(
        AllocateAddress,
        EfiRuntimeServicesData,
        EFI_SIZE_TO_PAGES(Length),
        &PhysAddr
    );

    if (EFI_ERROR(Status)) {
        return NULL;
    }

    VirtualAddr = (VOID*)(UINTN)PhysAddr;

    if (!Write) {
    }

    return VirtualAddr;
}
