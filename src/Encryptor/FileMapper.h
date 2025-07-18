#ifndef SYRIAL_ENCRYPTOR_FILEMAPPER_H
#define SYRIAL_ENCRYPTOR_FILEMAPPER_H

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/LoadedImage.h>
#include <Guid/FileInfo.h>

EFI_STATUS
LoadFile (
    IN CHAR16* FilePath,
    OUT UINT8** Buffer,
    OUT UINTN* BufferSize
);

EFI_STATUS
SaveFile (
    IN CHAR16* FilePath,
    IN UINT8* Buffer,
    IN UINTN BufferSize
);

#endif 
