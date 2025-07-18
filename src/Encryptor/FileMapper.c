#include "FileMapper.h"

STATIC EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* GetFileSystem()
{
    EFI_STATUS Status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem = NULL;

    EFI_LOADED_IMAGE_PROTOCOL* LoadedImage = NULL;
    Status = gBS->HandleProtocol(
        gImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID**)&LoadedImage
    );
    if (EFI_ERROR(Status)) return NULL;

    Status = gBS->HandleProtocol(
        LoadedImage->DeviceHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID**)&FileSystem
    );
    if (EFI_ERROR(Status)) return NULL;

    return FileSystem;
}

EFI_STATUS
LoadFile (
    IN CHAR16* FilePath,
    OUT UINT8** Buffer,
    OUT UINTN* BufferSize
) {
    EFI_FILE_PROTOCOL* Root;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FS = GetFileSystem();
    if (!FS) return EFI_NOT_FOUND;

    EFI_STATUS Status = FS->OpenVolume(FS, &Root);
    if (EFI_ERROR(Status)) return Status;

    EFI_FILE_PROTOCOL* File;
    Status = Root->Open(Root, &File, FilePath, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(Status)) return Status;

    EFI_FILE_INFO* FileInfo;
    UINTN InfoSize = sizeof(EFI_FILE_INFO) + 256;
    FileInfo = AllocateZeroPool(InfoSize);
    if (!FileInfo) return EFI_OUT_OF_RESOURCES;

    Status = File->GetInfo(File, &gEfiFileInfoGuid, &InfoSize, FileInfo);
    if (EFI_ERROR(Status)) {
        File->Close(File);
        return Status;
    }

    UINTN Size = FileInfo->FileSize;
    *Buffer = AllocateZeroPool(Size);
    if (!*Buffer) {
        File->Close(File);
        return EFI_OUT_OF_RESOURCES;
    }

    *BufferSize = Size;
    Status = File->Read(File, &Size, *Buffer);
    File->Close(File);
    return Status;
}

EFI_STATUS
SaveFile (
    IN CHAR16* FilePath,
    IN UINT8* Buffer,
    IN UINTN BufferSize
) {
    EFI_FILE_PROTOCOL* Root;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FS = GetFileSystem();
    if (!FS) return EFI_NOT_FOUND;

    EFI_STATUS Status = FS->OpenVolume(FS, &Root);
    if (EFI_ERROR(Status)) return Status;

    EFI_FILE_PROTOCOL* File;
    Status = Root->Open(Root, &File, FilePath,
                        EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    if (EFI_ERROR(Status)) return Status;

    Status = File->SetPosition(File, 0);
    if (EFI_ERROR(Status)) {
        File->Close(File);
        return Status;
    }

    Status = File->Write(File, &BufferSize, Buffer);
    File->Close(File);
    return Status;
}
