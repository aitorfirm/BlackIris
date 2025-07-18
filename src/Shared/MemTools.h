#ifndef SYRIAL_SHARED_MEMTOOLS_H
#define SYRIAL_SHARED_MEMTOOLS_H

#include <Uefi.h>

VOID* MapPhysicalMemory(EFI_PHYSICAL_ADDRESS Address, UINTN Size);
VOID  UnmapMemory(VOID* VirtualAddress, UINTN Size);

BOOLEAN ReadPhysMem(EFI_PHYSICAL_ADDRESS Address, VOID* Buffer, UINTN Size);
BOOLEAN WritePhysMem(EFI_PHYSICAL_ADDRESS Address, CONST VOID* Buffer, UINTN Size);

VOID* FindPattern(VOID* Base, UINTN Size, CONST UINT8* Pattern, CONST CHAR* Mask);

#endif
