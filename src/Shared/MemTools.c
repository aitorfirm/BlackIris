#include "MemTools.h"
#include <Library/UefiBootServicesTableLib.h>
#include "Logger.h"

VOID* MapPhysicalMemory(EFI_PHYSICAL_ADDRESS Address, UINTN Size) {
    EFI_PHYSICAL_ADDRESS Aligned = Address & ~0xFFF; // 4KB aligned
    UINTN AlignedSize = Size + (Address - Aligned);

    VOID* VirtualAddress = NULL;
    EFI_STATUS Status = gBS->AllocatePages(AllocateAnyPages, EfiRuntimeServicesData,
                                           EFI_SIZE_TO_PAGES(AlignedSize), &Aligned);

    if (EFI_ERROR(Status)) {
        LogError(L"fAiLed to map memory");
        return NULL;
    }

    VirtualAddress = (VOID*)(UINTN)Aligned;
    return (VOID*)((UINT8*)VirtualAddress + (Address - Aligned));
}

VOID UnmapMemory(VOID* VirtualAddress, UINTN Size) {
    EFI_PHYSICAL_ADDRESS PhysAddr = (EFI_PHYSICAL_ADDRESS)(UINTN)VirtualAddress;
    gBS->FreePages(PhysAddr, EFI_SIZE_TO_PAGES(Size));
}

BOOLEAN ReadPhysMem(EFI_PHYSICAL_ADDRESS Address, VOID* Buffer, UINTN Size) {
    VOID* Mapped = MapPhysicalMemory(Address, Size);
    if (!Mapped) return FALSE;

    for (UINTN i = 0; i < Size; i++)
        ((UINT8*)Buffer)[i] = ((UINT8*)Mapped)[i];

    UnmapMemory(Mapped, Size);
    return TRUE;
}

BOOLEAN WritePhysMem(EFI_PHYSICAL_ADDRESS Address, CONST VOID* Buffer, UINTN Size) {
    VOID* Mapped = MapPhysicalMemory(Address, Size);
    if (!Mapped) return FALSE;

    for (UINTN i = 0; i < Size; i++)
        ((UINT8*)Mapped)[i] = ((UINT8*)Buffer)[i];

    UnmapMemory(Mapped, Size);
    return TRUE;
}

VOID* FindPattern(VOID* Base, UINTN Size, CONST UINT8* Pattern, CONST CHAR* Mask) {
    for (UINTN i = 0; i <= Size - 1; i++) {
        BOOLEAN Found = TRUE;
        for (UINTN j = 0; Mask[j]; j++) {
            if (Mask[j] != '?' && ((UINT8*)Base)[i + j] != Pattern[j]) {
                Found = FALSE;
                break;
            }
        }
        if (Found) return (VOID*)((UINT8*)Base + i);
    }
    return NULL;
}
