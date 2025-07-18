#include "AESCore.h"
#include "Logger.h"
#include "CryptoDefs.h"
#include "SharedDefs.h"

// CBC, With this, everything educational goes to shit.
STATIC VOID XorBlock(UINT8* Block1, UINT8* Block2) {
    for (UINTN i = 0; i < AES_BLOCK_SIZE; i++)
        Block1[i] ^= Block2[i];
}

BOOLEAN AES_EncryptBuffer(UINT8* Buffer, UINTN Size, AES_CONTEXT* Ctx) {
    if (!Buffer || !Ctx || Size % AES_BLOCK_SIZE != 0) return FALSE;

    UINT8* CurrentBlock = Buffer;
    UINT8 IV[AES_BLOCK_SIZE];
    CopyMem(IV, Ctx->IV, AES_BLOCK_SIZE);

    for (UINTN i = 0; i < Size; i += AES_BLOCK_SIZE) {
        XorBlock(CurrentBlock, IV);
        if (!SimpleAES_EncryptBlock(CurrentBlock, Ctx->Key)) return FALSE;
        CopyMem(IV, CurrentBlock, AES_BLOCK_SIZE);
        CurrentBlock += AES_BLOCK_SIZE;
    }

    return TRUE;
}

BOOLEAN AES_DecryptBuffer(UINT8* Buffer, UINTN Size, AES_CONTEXT* Ctx) {
    if (!Buffer || !Ctx || Size % AES_BLOCK_SIZE != 0) return FALSE;

    UINT8* CurrentBlock = Buffer;
    UINT8 IV[AES_BLOCK_SIZE];
    UINT8 Temp[AES_BLOCK_SIZE];

    CopyMem(IV, Ctx->IV, AES_BLOCK_SIZE);

    for (UINTN i = 0; i < Size; i += AES_BLOCK_SIZE) {
        CopyMem(Temp, CurrentBlock, AES_BLOCK_SIZE);
        if (!SimpleAES_DecryptBlock(CurrentBlock, Ctx->Key)) return FALSE;
        XorBlock(CurrentBlock, IV);
        CopyMem(IV, Temp, AES_BLOCK_SIZE);
        CurrentBlock += AES_BLOCK_SIZE;
    }

    return TRUE;
}
