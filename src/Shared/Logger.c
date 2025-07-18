#include "Logger.h"
#include <Library/UefiBootServicesTableLib.h>

static BOOLEAN gVerboseEnabled = FALSE;

VOID InitLogger(BOOLEAN EnableVerbose) {
    gVerboseEnabled = EnableVerbose;
    if (gST && gST->ConOut) {
        gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE);
        gST->ConOut->OutputString(gST->ConOut, L"Logger in!\n");
    }
}

VOID LogInfo(CONST CHAR16* Msg) {
    if (!gVerboseEnabled) return;
    if (gST && gST->ConOut) {
        gST->ConOut->SetAttribute(gST->ConOut, EFI_LIGHTGRAY);
        gST->ConOut->OutputString(gST->ConOut, L"[INFO] ");
        gST->ConOut->OutputString(gST->ConOut, Msg);
        gST->ConOut->OutputString(gST->ConOut, L"\n");
    }
}

VOID LogWarn(CONST CHAR16* Msg) {
    if (!gVerboseEnabled) return;
    if (gST && gST->ConOut) {
        gST->ConOut->SetAttribute(gST->ConOut, EFI_YELLOW);
        gST->ConOut->OutputString(gST->ConOut, L"[WARN] ");
        gST->ConOut->OutputString(gST->ConOut, Msg);
        gST->ConOut->OutputString(gST->ConOut, L"\n");
    }
}

VOID LogError(CONST CHAR16* Msg) {
    if (!gVerboseEnabled) return;
    if (gST && gST->ConOut) {
        gST->ConOut->SetAttribute(gST->ConOut, EFI_RED);
        gST->ConOut->OutputString(gST->ConOut, L"[ERROR] ");
        gST->ConOut->OutputString(gST->ConOut, Msg);
        gST->ConOut->OutputString(gST->ConOut, L"\n");
    }
}

VOID LogRaw(CONST CHAR16* Msg) {
    if (!gST || !gST->ConOut) return;
    gST->ConOut->SetAttribute(gST->ConOut, EFI_LIGHTGRAY);
    gST->ConOut->OutputString(gST->ConOut, Msg);
}
