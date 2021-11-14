# a2560-elf target for VBCC

The contents of the `vbcc` folder should be copied into your VBCC installation.

## Usage

An executable can be produced using the following command:
```bash
vc +a256-elf -o hello.elf hello.c
```
If on a Windows machine, use the following:
```bash
vc +a256-elf-win32 -o hello.elf hello.c
```

## Build

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