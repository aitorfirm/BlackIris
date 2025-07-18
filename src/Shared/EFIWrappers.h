#ifndef SYRIAL_SHARED_EFIWRAPPERS_H
#define SYRIAL_SHARED_EFIWRAPPERS_H

#include <Uefi.h>

VOID* EfiAlloc(UINTN Size);
VOID  EfiFree(VOID* Ptr);

EFI_STATUS EfiGetVar(CONST CHAR16* Name, EFI_GUID* Guid, VOID* Buffer, UINTN* Size);
EFI_STATUS EfiSetVar(CONST CHAR16* Name, EFI_GUID* Guid, VOID* Buffer, UINTN Size);

VOID* EfiLocateProtocol(EFI_GUID* ProtocolGuid);

VOID  EfiPrint(CONST CHAR16* Msg);

#endif 
