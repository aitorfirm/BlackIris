<h1 align="center">
   Blackiris UEFI Rootkit
</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Architecture-UEFI%20x64-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Persistence-ExitBootServices%20Hook-red?style=for-the-badge">
  <img src="https://img.shields.io/badge/Language-C%2B%2B%20%7C%20C%20%7C%20ASM-yellow?style=for-the-badge">
</p>

<p align="center">
  <b>BlackIris</b> is a full-scale, modular UEFI rootkit with physical memory mapping, runtime persistence, remote command control, file encryption, and a keyserver backend. It executes below the OS using real UEFI Runtime Services and survives Secure Boot bypass.
</p>

---

## Project Overview

Syrial & BlackIris is a **modular rootkit for UEFI-based systems**, structured into core functional sections:

- Direct boot-time persistence via `ExitBootServices` hook.
- Memory mapping via [`MmMapIoSpace()`]([https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nc-wdm-mm_map_io_space](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-mmmapiospace)).
- Runtime payload execution before and after OS boot.
- Live keylogging and command execution.
- Encrypted file system layer.
- Secure backend keyserver written in Node.js, C++, and C#.

---

## Architecture

src/
```bash
├── Boot/ ← EFI entry point, memory patching, DXE hook, interrupt hijacking
├── KernelMode/ ← Keylogger, command control, remote ops
├── Encryptor/ ← AES/XOR crypto, filesystem encryption, keygen
├── Shared/ ← Logging, memory utils, EFI wrappers, syscall bridge
└── Syrial.inf ← UEFI build descriptor for EDK2
```

## aFckingFeatures

-  **UEFI Runtime Execution**  
  Syrial executes before the operating system, hooking `ExitBootServices` and maintaining control from DXE to runtime.

-  **Physical Memory Mapping**  
  Using `MmMapIoSpace()`, Syrial accesses physical memory with full privileges.

-  **Command Execution & Remote Control**  
  Custom TCP/command listener in UEFI context with support for remote operation modules.

-  **UEFI-Level Keylogger**  
  Records keystrokes during pre-boot, EFI Shell, or early OS boot time.

-  **Filesystem Encryption Engine**  
  AES-256 and XOR-based encryptor for files and logs, handled in `Encryptor/`.

-  **External Key Server**  
  Key delivery and AES/XOR updates powered by a backend written in Node.js/C++/C#.

-  **Persistent Loader**  
  Loader handles SMRAM/SMI patching and launches `KernelMain` from mapped runtime region.

-  **Custom EDK2 Build**  
  Fully EDK2-compatible with clean `.inf`, separate compilation units, and logical linking.

---

## 🔧 Build Instructions

> BlackIris is intended to be compiled with [EDK2](https://github.com/tianocore/edk2) under a UEFI development environment.

### Dependencies

- EDK2 environment (Windows/Linux)
- GCC or CLANG cross compiler (targeting `x86_64`)
- Node.js (for backend server)
- g++ (for key rotator)
- .NET SDK (for Windows client)

### Compilation

1. Clone the repo and place it in your EDK2 workspace.
2. Update your `target.txt` to include the path to `Syrial.inf`.
3. Build with:

```bash
build -a X64 -p Syrial/Syrial.inf
