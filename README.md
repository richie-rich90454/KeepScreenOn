# KeepScreenOn – Prevent Windows Sleep & Keep Screen Awake (Native C, No Dependencies)

A minimal, standalone Windows utility that stops the display from turning off
and prevents the system from sleeping. Written in plain C using only the
Windows API. No browser, no runtime, no bloat.

## Why KeepScreenOn?

Most “keep awake” tools run inside a web browser, consume hundreds of
megabytes of RAM and require constant user interaction. KeepScreenOn is
different:

- **Native C executable** – compiles to a tiny, self-contained `.exe` with
  no external libraries.
- **No C runtime** – uses a custom entry point to keep the binary and memory
  footprint as low as possible.
- **Zero network activity** – no analytics, no tracking, no hidden requests.
- **Resizable window** – a simple GUI with a toggle button and status text.
- **Clean resource management** – restores normal power settings when closed.

**Keywords:** keep screen on, prevent sleep, screen awake, display always on,
insomnia, Windows power management, tiny C program, no dependencies, native
Win32 utility.

## How It Works

The program calls the official Windows API
[`SetThreadExecutionState`](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setthreadexecutionstate)
with `ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED | ES_CONTINUOUS`. This tells
Windows that the display and system must remain active. No timers, no periodic
wake-ups, no background threads — just one API call that runs until you
deactivate it or close the window.

## Build

All commands produce a static, CRT‑free executable. Choose the compiler that
matches your setup.

**GCC (MinGW‑w64)**
```bash
gcc -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,65536 -mwindows -o KeepScreenOn.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32
```

**MSVC (Developer Command Prompt)**
```bash
cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup kernel32.lib user32.lib gdi32.lib
```

**Clang (MinGW target)**
```bash
clang -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,65536 -mwindows -o KeepScreenOn.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32
```

**Clang‑CL (MSVC‑compatible)**
```bash
clang-cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup kernel32.lib user32.lib gdi32.lib
```

## Usage

Run `KeepScreenOn.exe`. Click the **Turn On** button to activate screen‑awake
mode. The status label changes to **Status: On** and your display will stay
bright indefinitely. Click again to restore normal power saving. Closing the
window also restores the original sleep settings.

## Memory Efficiency

To minimize resource usage, the binary is compiled without the standard C
runtime (`-nostdlib`), the default stack reservation is reduced and unused
code sections are stripped by the linker. The result is an ultra‑light
process that uses only a fraction of the memory consumed by typical
background utilities.

## License

MIT — do whatever you want with the code. See [LICENSE](LICENSE).

## Author

`richie-rich90454` written in 2026

---

*If you find this tool useful, consider starring the repository to help
others discover a simpler way to keep their screen on.*