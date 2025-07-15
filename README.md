# Parallel-Pi: Multithreaded Estimation of Pi Using Maclaurin Series

## Project Overview

This project implements a multithreaded approach to estimate the value of π using the **Maclaurin series for arctangent(1)**:

> π ≈ 4 × (1 - 1/3 + 1/5 - 1/7 + 1/9 - ...)

The computation is parallelized using **POSIX threads (pthreads)** with proper synchronization through **mutex locks** to avoid race conditions and ensure thread-safe access to shared memory.

Developed as a **Complex Computing Problem (CCP)** for the course **Operating Systems (CC3011)** at the **University of Management and Technology**.

---

## Features

- ✅ Multithreaded Pi estimation
- ✅ Mutex-based synchronization
- ✅ Load-balanced computation
- ✅ Comparison with sequential implementation
- ✅ Flowcharts and technical documentation

