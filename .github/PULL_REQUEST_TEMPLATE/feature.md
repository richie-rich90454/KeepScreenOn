---
name: New feature
about: Add a new feature to KeepScreenOn
title: ''
labels: enhancement
assignees: ''
---

**Description of the feature**
What does this pull request add or change?

**Motivation**
Why is this feature useful? Does it solve a specific user need?

**Implementation outline**
Briefly describe how the feature was implemented (new function, modified UI, etc.).

**Impact on size and memory**
- [ ] The binary remains CRT‑free and compiles with `-nostdlib`
- [ ] No new external libraries or dependencies have been introduced
- [ ] Memory footprint has not increased measurably (test with Task Manager)
- [ ] The feature respects the current minimal design philosophy

**Testing performed**
- [ ] Compiled with all three toolchains (GCC, MSVC, Clang)
- [ ] Tested on a modern Windows version
- [ ] Window resizing, button toggle, and close‑restore still work correctly
- [ ] Windows 95 compatibility (fallback path) is not affected

**Screenshots (if applicable)**

**Additional context**