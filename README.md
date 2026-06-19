# KeepScreenOn – Prevent Windows Sleep & Keep Screen Awake

A minimal, standalone Windows utility that stops the display from turning off
and prevents the system from sleeping. Written in plain C using only the
Windows API. No browser, no runtime, no heavy dependencies.

## Why KeepScreenOn?

Most “keep awake” tools run inside a web browser, consume hundreds of
megabytes of RAM and require constant user interaction. KeepScreenOn is
different:

- **Native C executable** – compiles to a tiny, self-contained `.exe` with
  no external libraries.
- **No C runtime** – uses a custom entry point to keep the binary and memory
  footprint as low as possible.
- **Windows 95+ compatible** – uses `SetThreadExecutionState` on Windows 98
  and later; falls back to `SystemParametersInfo` on Windows 95 to disable
  the screen saver and monitor power-off. Both paths are legitimate, documented
  Win32 APIs — no trickery.
- **Zero network activity** – no analytics, no tracking, no hidden requests.
- **Resizable window** – a simple GUI with a toggle button and status text.
- **Clean resource management** – restores normal power settings when closed.

**Keywords:** keep screen on, prevent sleep, screen awake, display always on,
insomnia, Windows power management, Windows 95 compatible, tiny C program,
no dependencies, native Win32 utility, SetThreadExecutionState, CRT‑free,
low memory, lightweight, richie‑rich90454.

## How It Works

On Windows 98 and later, the program calls the official Windows API
[`SetThreadExecutionState`](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setthreadexecutionstate)
with `ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED | ES_CONTINUOUS`. This tells
Windows that the display and system must remain active.

On Windows 95, where that function does not exist, the program uses
`SystemParametersInfo` to disable the screen saver and monitor low-power
and power-off timeouts. Original settings are saved when you click **Turn On**
and restored when you click **Turn Off** or close the window.

No timers, no periodic wake‑ups, no background threads — just one API call
that runs until you deactivate it or close the window.

## Build

All commands produce a static, CRT‑free executable. Choose the 32‑bit or
64‑bit version depending on your target system.

**GCC (MinGW‑w64) – 64‑bit**
```bash
gcc -m64 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,8192 -mwindows -o KeepScreenOn64.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32
```

**GCC (MinGW‑w64) – 32‑bit (requires i686 MinGW package)**
```bash
gcc -m32 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,8192 -mwindows -o KeepScreenOn32.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32
```

**MSVC – 64‑bit (x64 Native Tools Command Prompt)**
```bash
cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn64.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup /STACK:8192 kernel32.lib user32.lib gdi32.lib
```

**MSVC – 32‑bit (x86 Native Tools Command Prompt)**
```bash
cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn32.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup /STACK:8192 kernel32.lib user32.lib gdi32.lib
```

**Clang (MinGW target) – 64‑bit**
```bash
clang -m64 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,8192 -mwindows -o KeepScreenOn64.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32
```

**Clang (MinGW target) – 32‑bit**
```bash
clang -m32 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,8192 -mwindows -o KeepScreenOn32.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32
```

**Clang‑CL (MSVC‑compatible, x64 environment)**
```bash
clang-cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn64.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup /STACK:8192 kernel32.lib user32.lib gdi32.lib
```

**Clang‑CL (MSVC‑compatible, x86 environment)**
```bash
clang-cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn32.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup /STACK:8192 kernel32.lib user32.lib gdi32.lib
```

## Usage

Run the appropriate `.exe`. Click the **Turn On** button to activate
screen‑awake mode. The status label changes to **Status: On** and your
display will stay bright indefinitely. Click again to restore normal power
saving. Closing the window also restores the original sleep settings.

## Memory Efficiency

To minimize resource usage, the binary is compiled without the standard C
runtime (`-nostdlib`), the stack reservation is reduced, and unused
code sections are stripped by the linker. After the window is shown, the
working set is aggressively trimmed. The result is an ultra‑light process
that uses only a fraction of the memory consumed by typical background
utilities.

## License

MIT — do whatever you want with the code. See [LICENSE](LICENSE).

## Author

`richie-rich90454` – 2026

---

*If you find this tool useful, consider starring the repository to help
others discover a simpler way to keep their screen on.*