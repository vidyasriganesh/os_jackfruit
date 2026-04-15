# Lightweight Container Engine in C

## Overview

This project implements a lightweight container runtime system in C, along with a Linux kernel module for monitoring resource usage. It demonstrates key operating system concepts including process isolation, inter-process communication (IPC), scheduling, and memory management.

---

## Features

### Container Engine
- Creation and management of multiple containers
- Process isolation using fork(), chroot(), and Linux namespaces
- Execution of custom commands within containers

### Supervisor System
- Central supervisor process to manage all containers
- Support for multiple concurrent containers
- Tracks container metadata such as PID, status, and uptime

### CLI Communication
- Communication between CLI and supervisor using UNIX domain sockets
- Supported commands:
  - start
  - stop
  - ps
  - logs

### Logging System
- Bounded buffer implementation for logging
- Logs captured via pipes
- Dedicated logging thread writes logs to files

### Memory Monitoring (Kernel Module)
- Custom kernel module (monitor.c)
- Detects:
  - Soft memory limit violations
  - Hard memory limit violations
- Logs generated via kernel logging (dmesg)

### CPU Scheduling Experiment
- Demonstrates the effect of nice values on process scheduling
- Shows impact of priority on execution time

---

## Project Structure

boilerplate/
│── engine.c          # Container runtime and CLI
│── monitor.c         # Kernel module for memory monitoring
│── cpu_task.c        # CPU scheduling experiment
│── memory_hog.c      # Memory stress program
│── io_pulse.c        # I/O workload generator
│── Makefile          # Build configuration
│── rootfs/           # Root filesystem for containers
│── screenshots/      # Output screenshots

---

## Build Instructions

### Compile the Project
make

### Load the Kernel Module
sudo insmod monitor.ko

### Verify Module Installation
lsmod | grep monitor

---

## Usage

### Start Supervisor
sudo ./engine supervisor $(pwd)/rootfs

### Start Containers
./engine start alpha $(pwd)/rootfs /bin/sh
./engine start beta  $(pwd)/rootfs /bin/sh

### List Running Containers
./engine ps

### View Logs
./engine logs alpha

### Stop a Container
./engine stop alpha

---

## Experiments and Results

- Multi-container supervision under a single supervisor process
- Container metadata tracking (PID, status, uptime)
- Logging system using bounded buffer and pipes
- CLI communication via UNIX domain sockets
- Detection of soft and hard memory limits
- CPU scheduling behavior based on nice values
- Clean container termination without zombie processes

---

## Technologies Used

- C Programming Language
- Linux System Calls
- UNIX Domain Sockets
- Linux Kernel Modules
- Process Scheduling (nice values)

---

## Concepts Covered

- Process Management
- Inter-Process Communication (IPC)
- Memory Management
- Kernel-Level Programming
- CPU Scheduling

---

## Conclusion

This project provides a practical understanding of container runtime internals, along with kernel-level monitoring and scheduling mechanisms in Linux. It serves as a compact demonstration of core operating system principles applied in a real-world system.

---

## Author

Vidyasri Ganesh

---

## Notes

- Run commands with sudo where required
- Ensure Linux kernel headers are installed before building the module
- Tested on Ubuntu Linux
