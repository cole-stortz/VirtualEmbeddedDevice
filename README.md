# Virtual Embedded Device Simulator

A full-stack embedded systems simulation that mirrors real-world IoT and industrial device architectures. A virtual device (C++) communicates with a TCP server (Python) over a custom protocol, with a real-time adaptive UI dashboard that dynamically reflects the device's configuration.

---

## Overview

This project simulates the complete communication pipeline between an embedded device and a control system — the same architecture used in robotics, IoT platforms, and industrial control systems. Rather than requiring physical hardware, all device components are virtualized and communicate over TCP/IP.

---

## Features

### Virtual Device (C++)
- Simulates a real embedded system listening for incoming TCP connections
- Processes commands from the server and responds with state/data
- Modular component system supporting:
  - **LEDs** — status indicators and visual feedback
  - **Buttons** — user input and control interfaces
  - **Sensors** — environmental data simulation (temperature, light, distance)
  - **Motors** — actuator simulation for movement and mechanical actions

### TCP Server + Dashboard (Python)
- Acts as the controller, sending commands and receiving device data
- **Adaptive UI** — automatically generates controls based on the connected device's configuration (no hardcoded interface)
- Real-time data visualization for all active sensors
- Command log / output terminal showing raw send/receive traffic
- Clean separation between communication layer and UI layer


---
