#include "EFIWrappers.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>

VOID* EfiAlloc(UINTN Size) {
    VOID* Ptr = NULL;
    if (gBS) {
        gBS->AllocatePool(EfiRuntimeServicesData, Size, &Ptr);
    }
    return Ptr;
}

VOID EfiFree(VOID* Ptr) {
    if (gBS && Ptr) {
        gBS->FreePool(Ptr);
    }
}

EFI_STATUS EfiGetVar(CONST CHAR16* Name, EFI_GUID* Guid, VOID* Buffer, UINTN* Size) {
    return gRT->GetVariable((CHAR16*)Name, Guid, NULL, Size, Buffer);
}

EFI_STATUS EfiSetVar(CONST CHAR16* Name, EFI_GUID* Guid, VOID* Buffer, UINTN Size) {
    return gRT->SetVariable((CHAR16*)Name, Guid,
                            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                            Size, Buffer);
}

VOID* EfiLocateProtocol(EFI_GUID* ProtocolGuid) {
    VOID* Interface = NULL;
    if (gBS) {
        gBS->LocateProtocol(ProtocolGuid, NULL, &Interface);
    }
    return Interface;
}

VOID EfiPrint(CONST CHAR16* Msg) {
    if (gST && gST->ConOut) {
        gST->ConOut->OutputString(gST->ConOut, (CHAR16*)Msg);
    }
}
