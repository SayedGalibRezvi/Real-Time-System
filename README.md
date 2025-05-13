
# FreeRTOS EDF Demo

This is a minimal FreeRTOS-based simulation using the POSIX port.
It simulates 4 tasks (T1–T4) scheduled under the EDF (Earliest Deadline First) algorithm.

## Task Set

| Task | WCET | Deadline |
|------|------|----------|
| T1   | 200  | 600      |
| T2   | 100  | 300      |
| T3   | 100  | 700      |
| T4   | 200  | 900      |

The EDFScheduler task dynamically assigns priorities based on earliest deadlines.

## How to Build & Run

```bash
make
./main
```
