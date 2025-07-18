#ifndef SYRIAL_BOOTKIT_LOADER_H
#define SYRIAL_BOOTKIT_LOADER_H

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS InitializeBootkit(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);

#endif 
