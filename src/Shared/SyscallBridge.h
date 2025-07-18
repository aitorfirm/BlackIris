#ifndef SYRIAL_SHARED_SYSCALLBRIDGE_H
#define SYRIAL_SHARED_SYSCALLBRIDGE_H

#include <Uefi.h>

BOOLEAN InjectRuntimeHook(VOID* Payload, UINTN Size);
BOOLEAN InstallSMIHandler(VOID* HandlerFunc);
BOOLEAN PrepareSyscallPatch(VOID* KernelBase, UINTN TableOffset);
VOID    BridgeToKernelMain();

VOID    WriteRuntimeData(VOID* Data, UINTN Size);

#endif
