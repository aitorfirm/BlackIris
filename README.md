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
