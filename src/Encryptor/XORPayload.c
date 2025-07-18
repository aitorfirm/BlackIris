#include "XORPayload.h"

VOID
XOR_EncryptBuffer (
    IN OUT UINT8* Buffer,
    IN UINTN      Length,
    IN CONST UINT8* Key,
    IN UINTN      KeyLen
) {
    if (!Buffer || !Key || KeyLen == 0 || Length == 0)
        return;

    for (UINTN i = 0; i < Length; i++) {
        Buffer[i] ^= Key[i % KeyLen];
        Buffer[i] = (Buffer[i] << 3) | (Buffer[i] >> 5);  // simple obfuscation
    }
}

VOID
XOR_DecryptBuffer (
    IN OUT UINT8* Buffer,
    IN UINTN      Length,
    IN CONST UINT8* Key,
    IN UINTN      KeyLen
) {
    if (!Buffer || !Key || KeyLen == 0 || Length == 0)
        return;

    for (UINTN i = 0; i < Length; i++) {
        Buffer[i] = (Buffer[i] >> 3) | (Buffer[i] << 5);  // reverse obfuscation
        Buffer[i] ^= Key[i % KeyLen];
    }
}
