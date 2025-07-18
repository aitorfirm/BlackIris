#ifndef SYRIAL_ENCRYPTOR_ENCRYPTFS_H
#define SYRIAL_ENCRYPTOR_ENCRYPTFS_H

#include <Uefi.h>
#include "CryptoDefs.h"
#include "XORPayload.h"
#include "FileMapper.h"

#define SYRIAL_AES_KEY_SIZE 32

EFI_STATUS
EncryptFile (
    IN CHAR16* FilePath,
    IN CONST UINT8* Key,
    IN UINTN KeyLength
);

EFI_STATUS
DecryptFile (
    IN CHAR16* FilePath,
    IN CONST UINT8* Key,
    IN UINTN KeyLength
);

#endif 
