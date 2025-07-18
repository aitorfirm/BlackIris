#include "KeyGen.h"
#include "SharedDefs.h"
#include "Logger.h"

STATIC EFI_STATUS GetEntropy(UINT8* Buffer, UINTN Size) {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_TIME Time;

    if (!Buffer || Size == 0) return EFI_INVALID_PARAMETER;

    gRT->GetTime(&Time, NULL);

    UINT64 Seed = ((UINT64)Time.Second << 56) |
                  ((UINT64)Time.Minute << 48) |
                  ((UINT64)Time.Hour   << 40) |
                  ((UINT64)Time.Day    << 32) |
                  ((UINT64)Time.Month  << 24) |
                  ((UINT64)Time.Year   << 16) |
                  ((UINT64)(UINTN)&Time);

    for (UINTN i = 0; i < Size; i++) {
        Seed ^= (Seed << 13);
        Seed ^= (Seed >> 7);
        Seed ^= (Seed << 17);
        Buffer[i] = (UINT8)(Seed & 0xFF);
    }

    return Status;
}

BOOLEAN GenerateSecureRandomBytes(UINT8* Buffer, UINTN Size) {
    if (!Buffer || Size == 0) return FALSE;
    EFI_STATUS Status = GetEntropy(Buffer, Size);
    return !EFI_ERROR(Status);
}

BOOLEAN GenerateRandomKeyAndIV(AES_CONTEXT* Context) {
    if (!Context) return FALSE;

    if (!GenerateSecureRandomBytes(Context->Key, AES_KEY_SIZE)) return FALSE;
    if (!GenerateSecureRandomBytes(Context->IV, AES_BLOCK_SIZE)) return FALSE;

    LOG("KeyGen: AES-256 key and IV generated successfully.");
    return TRUE;
}
// we dont use the OS's RNG - this runs before the OS
