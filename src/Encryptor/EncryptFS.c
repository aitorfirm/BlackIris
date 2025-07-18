#include "EncryptFS.h"

EFI_STATUS
EncryptFile (
    IN CHAR16* FilePath,
    IN CONST UINT8* Key,
    IN UINTN KeyLength
) {
    if (!FilePath || !Key || KeyLength == 0)
        return EFI_INVALID_PARAMETER;

    UINT8* Buffer = NULL;
    UINTN Size = 0;
    EFI_STATUS Status = LoadFile(FilePath, &Buffer, &Size);
    if (EFI_ERROR(Status) || Buffer == NULL)
        return Status;

    for (UINTN i = 0; i < Size; i += 16) {
        UINT8 Block[16] = {0};
        UINTN Remaining = (Size - i >= 16) ? 16 : Size - i;
        CopyMem(Block, &Buffer[i], Remaining);
        SimpleAES_EncryptBlock(Block, Key);
        CopyMem(&Buffer[i], Block, Remaining);
    }

    XOR_EncryptBuffer(Buffer, Size, Key, KeyLength);

    Status = SaveFile(FilePath, Buffer, Size);
    FreePool(Buffer);

    return Status;
}

EFI_STATUS
DecryptFile (
    IN CHAR16* FilePath,
    IN CONST UINT8* Key,
    IN UINTN KeyLength
) {
    if (!FilePath || !Key || KeyLength == 0)
        return EFI_INVALID_PARAMETER;

    UINT8* Buffer = NULL;
    UINTN Size = 0;
    EFI_STATUS Status = LoadFile(FilePath, &Buffer, &Size);
    if (EFI_ERROR(Status) || Buffer == NULL)
        return Status;

    XOR_DecryptBuffer(Buffer, Size, Key, KeyLength);

    for (UINTN i = 0; i < Size; i += 16) {
        UINT8 Block[16] = {0};
        UINTN Remaining = (Size - i >= 16) ? 16 : Size - i;
        CopyMem(Block, &Buffer[i], Remaining);
        SimpleAES_DecryptBlock(Block, Key);
        CopyMem(&Buffer[i], Block, Remaining);
    }

    Status = SaveFile(FilePath, Buffer, Size);
    FreePool(Buffer);

    return Status;
}
