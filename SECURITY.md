# Security Policy

## Supported Versions

Because KeepScreenOn is a single‑source‑file utility with no release track,
only the **latest commit** on the `main` branch is actively supported for
security patches. Older commits receive no guarantees.

| Version           | Supported          |
| ----------------- | ------------------ |
| Latest commit     | :white_check_mark: |
| Any prior commit  | :x:                |

## Reporting a Vulnerability

To report a suspected security vulnerability, please open a private issue at
[github.com/YOUR-USERNAME/KeepScreenOn/security/advisories](https://github.com/YOUR-USERNAME/KeepScreenOn/security/advisories)
or send an email to **your‑email@example.com** (replace with your actual
contact). Expect an initial response within 72 hours and a detailed assessment
within 7 days.

## What to Expect

- **Accepted vulnerabilities** – a patch will be prepared and included in the
  next commit. Credit will be given to the reporter unless anonymity is
  requested.
- **Declined reports** – a brief explanation will be provided, referencing the
  threat model of a locally‑run, no‑network, no‑data tool.

## Scope

KeepScreenOn is a local‑only executable that uses only documented Windows APIs.
It does **not** transmit or store user data, access the network, or run with
elevated privileges. As such, the attack surface is extremely small. Reports
are still welcomed and will be taken seriously.
