#include "InterruptHijack.h"
#include "../Shared/MemTools.h"
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>

typedef struct {
    UINT16 Limit;
    UINT64 Base;
} __attribute__((packed)) IDTR;

typedef struct {
    UINT16 OffsetLow;
    UINT16 Selector;
    UINT8  Ist;
    UINT8  TypeAttr;
    UINT16 OffsetMid;
    UINT32 OffsetHigh;
    UINT32 Zero;
} __attribute__((packed)) IDT_ENTRY;

STATIC IDTR OriginalIdtr;
STATIC IDT_ENTRY* IdtTable = NULL;
STATIC VOID* Trampoline = NULL;

VOID CustomHandler(); 

EFI_STATUS SetupInterruptHijack() {
    __asm__ volatile ("sidt %0" : "=m"(OriginalIdtr));

    IdtTable = (IDT_ENTRY*)(UINTN)(OriginalIdtr.Base);
    if (!IdtTable) return EFI_NOT_FOUND;

    UINT8 Vector = 0x80;

    IDT_ENTRY* Entry = &IdtTable[Vector];

    VOID* OriginalHandler = (VOID*)(
        ((UINT64)Entry->OffsetHigh << 32) |
        ((UINT64)Entry->OffsetMid << 16) |
        (UINT64)Entry->OffsetLow
    );

    
    Trampoline = MmMapIoSpace(0x100000, 0x1000, TRUE); 
    if (!Trampoline) return EFI_OUT_OF_RESOURCES;

    SetMem(Trampoline, 0x1000, 0x90); 
    *(UINT8*)Trampoline = 0xCC;      

    UINT64 Addr = (UINT64)(UINTN)Trampoline;
    Entry->OffsetLow = (UINT16)(Addr & 0xFFFF);
    Entry->Selector = 0x08; 
    Entry->Ist = 0;
    Entry->TypeAttr = 0x8E; 
    Entry->OffsetMid = (UINT16)((Addr >> 16) & 0xFFFF);
    Entry->OffsetHigh = (UINT32)((Addr >> 32) & 0xFFFFFFFF);
    Entry->Zero = 0;

    return EFI_SUCCESS;
}
