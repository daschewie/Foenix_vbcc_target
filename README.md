# Foenix targets for VBCC

Foenix A2560 build target for VBCC that produced ELF binaries.

## Install

The contents of the `vbcc` folder should be copied into your VBCC installation.

## Usage

Syscalls are availble by adding the following to your code:
```C
#include <mcp/syscalls.h>
```

An ELF executable can be produced using the following command:
```bash
vc +a2560-elf -o hello.elf hello.c
```
If on a Windows machine, use the following:
```bash
vc +a2560-elf-win32 -o hello.elf hello.c
```
---

An srec28 executable can be produced using the following command:
```bash
vc +a2560-s28 -o hello.s28 hello.c
```
If on a Windows machine, use the following:
```bash
vc +a2560-s28-win32 -o hello.s28 hello.c
```

## Build

For your convenience the libraries are prebuild in the `vbcc` directory and can be copied to you VBCC install. However, if you need to tweak the code:

- `startup.s` configures the entry point, defines syscall function, and calls sys_exit when main returns.
- `io.c` implements vbcc io stub funtions to enable stdio.
- `syscalls.c` implements sys_* kernel function via calls to syscall.

To build:
```bash
cd src
make

# to install into ../vbcc/targets/a2560-elf/lib
make install
```
