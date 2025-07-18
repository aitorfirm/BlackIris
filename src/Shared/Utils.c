#include "Utils.h"
#include "EFIWrappers.h"
#include <Library/UefiBootServicesTableLib.h>

UINTN StrLen(CONST CHAR16* Str) {
    UINTN Len = 0;
    while (Str && *Str++) Len++;
    return Len;
}

INTN StrCmp(CONST CHAR16* Str1, CONST CHAR16* Str2) {
    while (*Str1 && *Str2 && *Str1 == *Str2) {
        Str1++; Str2++;
    }
    return *Str1 - *Str2;
}

INTN StrnCmp(CONST CHAR16* Str1, CONST CHAR16* Str2, UINTN Count) {
    for (UINTN i = 0; i < Count; i++) {
        if (Str1[i] != Str2[i] || !Str1[i] || !Str2[i])
            return Str1[i] - Str2[i];
    }
    return 0;
}

VOID StrCpy(CHAR16* Dest, CONST CHAR16* Src) {
    while (*Src) *Dest++ = *Src++;
    *Dest = L'\0';
}

VOID StallMs(UINT64 Ms) {
    gBS->Stall((UINTN)(Ms * 1000));
}

UINT64 GetCurrentTimeMs(void) {
    EFI_TIME Time;
    gRT->GetTime(&Time, NULL);
    return (UINT64)Time.Second * 1000 + (UINT64)Time.Nanosecond / 1000000;
}

VOID MemCopy(VOID* Dest, CONST VOID* Src, UINTN Size) {
    for (UINTN i = 0; i < Size; i++)
        ((UINT8*)Dest)[i] = ((UINT8*)Src)[i];
}

VOID MemZero(VOID* Ptr, UINTN Size) {
    for (UINTN i = 0; i < Size; i++)
        ((UINT8*)Ptr)[i] = 0;
}

VOID HexDump(VOID* Ptr, UINTN Size) {
    UINT8* Bytes = (UINT8*)Ptr;
    for (UINTN i = 0; i < Size; i++) {
        if (i % 16 == 0)
            Print(L"\n%04x: ", i);
        Print(L"%02x ", Bytes[i]);
    }
    Print(L"\n");
}
