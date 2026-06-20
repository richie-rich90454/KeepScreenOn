# Contributing to KeepScreenOn

Thank you for considering a contribution. This document explains how to
propose changes, report problems, and submit code.

## Getting Started

1. **Fork** the repository and clone it locally.
2. Create a branch for your work:
   ```bash
   git checkout -b my-improvement
   ```
3. Build the project to confirm your environment works before making
   changes. Pick the command that matches your compiler from the
   [README](README.md).
4. Make your changes in `KeepScreenOn.c`. The entire program lives in one
   file—no additional headers, no build system, no dependencies.

## Reporting Issues

- Use the **Issues** tab to report bugs or request features.
- Include the Windows version, compiler, and steps to reproduce the
  problem.
- Security-sensitive reports should follow the
  [Security Policy](SECURITY.md).

## Pull Request Guidelines

- Keep changes minimal and focused. If you are fixing multiple unrelated
  items, open separate pull requests.
- Follow the existing coding style:
  - No spaces around operators inside expressions (`a=b` not `a = b`).
  - No blank lines beyond what the original file uses.
  - Comments are only allowed in the top block; do not add inline
    comments.
- The program must remain **CRT‑free** (`-nostdlib`) and compile with
  **GCC, MSVC, and Clang** using the commands in the README.
- Test your change on at least one modern Windows version, and if
  possible, verify it does not break the Windows 95 fallback path.
- If your change alters behavior, update the **Usage** or **How It Works**
  sections of the README.
- Run the compiled `.exe` and click the button a few times to ensure no
  visual glitches or memory leaks.

## Code of Conduct

Be respectful. Treat others as you would in a professional workplace.

## Questions

For general questions, open an issue or contact the author at
[richard@richardsblogs.com](mailto:richard@richardsblogs.com).
