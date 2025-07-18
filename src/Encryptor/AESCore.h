#ifndef SYRIAL_ENCRYPTOR_AESCORE_H
#define SYRIAL_ENCRYPTOR_AESCORE_H

#include <Uefi.h>

#define AES_KEY_SIZE 32 // AES-256
#define AES_BLOCK_SIZE 16

typedef struct {
    UINT8 Key[AES_KEY_SIZE];
    UINT8 IV[AES_BLOCK_SIZE];
} AES_CONTEXT;

BOOLEAN AES_EncryptBuffer(UINT8* Buffer, UINTN Size, AES_CONTEXT* Ctx);
BOOLEAN AES_DecryptBuffer(UINT8* Buffer, UINTN Size, AES_CONTEXT* Ctx);

#endif 
