#ifndef SYRIAL_ENCRYPTOR_XORPAYLOAD_H
#define SYRIAL_ENCRYPTOR_XORPAYLOAD_H

#include <Uefi.h>
#include "CryptoDefs.h"
#include "SharedDefs.h"

VOID
XOR_EncryptBuffer (
    IN OUT UINT8* Buffer,
    IN UINTN      Length,
    IN CONST UINT8* Key,
    IN UINTN      KeyLen
);

VOID
XOR_DecryptBuffer (
    IN OUT UINT8* Buffer,
    IN UINTN      Length,
    IN CONST UINT8* Key,
    IN UINTN      KeyLen
);

#endif 
