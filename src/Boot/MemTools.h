#ifndef SYRIAL_SHARED_MEMTOOLS_H
#define SYRIAL_SHARED_MEMTOOLS_H

#include <Uefi.h>

VOID* MmMapIoSpace(IN EFI_PHYSICAL_ADDRESS PhysAddr, IN UINTN Length, IN BOOLEAN Write);

#endif 
