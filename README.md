# OS-Project

A comparative study of **linear search** performance across three concurrency models in C:
single-threaded, multi-threaded, and multi-process — with implementations for both **Unix** and **Windows**.

---

## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Usage](#usage)
- [Performance Comparison](#performance-comparison)
- [License](#license)

---

## Overview

This project benchmarks the time it takes to search for a value in a large integer array using three different execution strategies:

| Strategy | Unix | Windows |
|---|---|---|
| Single-threaded | `unix/singleMain.c` | `win/singleMain.c` |
| Multi-threaded | `unix/MThreadMain.c` | `win/MThreadMain.c` |
| Multi-process | `unix/MProcMain.c` | `win/MProcMain.c` |

Each program fills an array of `N` elements with the sequence `0, 2, 4, …, 2*(N-1)`, searches for a target value `X`, reports the index where it was found (if any), and prints the elapsed wall-clock time.

---

## Project Structure

```
OS-Project/
├── unix/
│   ├── singleMain.c   # Sequential search
│   ├── MThreadMain.c  # Parallel search using POSIX threads (pthreads, 4 threads)
│   ├── MProcMain.c    # Parallel search using fork() (10 child processes)
│   └── Makefile
├── win/
│   ├── singleMain.c   # Sequential search
│   ├── MThreadMain.c  # Parallel search using Win32 threads (8 threads)
│   ├── MProcMain.c    # Parallel search using fork() via windows.h
│   └── Makefile
└── README.md
```

---

## How It Works

### Single-threaded (`singleMain.c`)
Performs a straightforward linear scan of the entire array in one thread, recording the elapsed time with `clock()`.

### Multi-threaded (`MThreadMain.c`)
Divides the array into equal-sized chunks and assigns each chunk to a separate thread:

- **Unix** — uses POSIX `pthread_create` / `pthread_join` (4 threads).
- **Windows** — uses Win32 `CreateThread` / `WaitForSingleObject` (8 threads).

### Multi-process (`MProcMain.c`)
Divides the array into equal-sized chunks and spawns a separate process for each chunk:

- **Unix** — uses `fork()` and `wait()` (10 child processes).
- **Windows** — uses the Win32 process API via `windows.h`.

Each child process independently scans its portion of the array and prints the result if the element is found.

---

## Prerequisites

### Unix / Linux / macOS
- GCC or Clang (`cc`)
- POSIX-compatible environment (Linux, macOS, WSL)
- `make`

### Windows
- MinGW-w64 or MSVC with a compatible `make` tool
- Windows SDK headers (`windows.h`)

---

## Building

### Unix

```bash
cd unix
make        # builds all three targets: single, thread, proc
make clean  # removes compiled binaries
```

Individual targets:

```bash
make single   # builds ./single
make thread   # builds ./thread
make proc     # builds ./proc
```

### Windows

```bash
cd win
make
```

---

## Usage

All three programs share the same command-line interface:

```
<binary> <array_size> <search_value>
```

| Argument | Description |
|---|---|
| `array_size` | Number of elements in the array |
| `search_value` | The value to search for |

> **Note:** The array is populated with even numbers `(0, 2, 4, …)`, so a search value must be an even number less than `2 * array_size` to guarantee a match.

### Examples

```bash
# Single-threaded search in an array of 1,000,000 elements, looking for 999998
./single 1000000 999998

# Multi-threaded search
./thread 1000000 999998

# Multi-process search
./proc 1000000 999998
```

Sample output:

```
Element is present at index 499999 time that spend to search 0.003241
```

---

## Performance Comparison

Running all three programs with the same arguments lets you directly compare execution times:

```bash
./single 10000000 9999998
./thread 10000000 9999998
./proc   10000000 9999998
```

Expected observations:
- **Single-threaded** is the baseline.
- **Multi-threaded** reduces search time by parallelising across CPU cores, with lower overhead than multi-process.
- **Multi-process** incurs higher startup overhead (process creation) but fully isolates each worker.

---

## License

This project is released under the [MIT License](LICENSE).

