#ifndef SYRIAL_ENCRYPTOR_KEYGEN_H
#define SYRIAL_ENCRYPTOR_KEYGEN_H

#include <Uefi.h>
#include "AESCore.h"

BOOLEAN GenerateRandomKeyAndIV(AES_CONTEXT* Context);
BOOLEAN GenerateSecureRandomBytes(UINT8* Buffer, UINTN Size);

#endif 
// Im tired of fucking your ass rn 🤐
