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
  - **Sensors** — environmental data simulation (temperature, light, distance, color)
  - **Motors** — actuator simulation for movement and mechanical actions

### TCP Server + Dashboard (Python)
- Acts as the controller, sending commands and receiving device data
- **Adaptive UI** — automatically generates controls based on the connected device's configuration (no hardcoded interface)
- Real-time data visualization for all active sensors
- Command log / output terminal showing raw send/receive traffic
- Clean separation between communication layer and UI layer


## TODO

### Device (C++)
- [ ] Begin Development...
- [ ] Develop embedded system loop
- [ ] Develop layout JSON
- [ ] Develop communication link with Controller/Server as client
  #### Device Addons
    - [ ] Motor
    - [ ] Sensors
    - [ ] LEDs
    - [ ] Buttons/Switches
---
### Server (Python)
- [ ] Begin Development...
- [ ] Develop communication link with Device/client as server
- [ ] Develop log
- [ ] Develop UI elements according to layout JSON
- [ ] Develop link with Dashboard to display configured UI elements
---
### Dashboard
- [ ] Begin Development...
- [ ] Display configured UI elements according to server configuration
---
### Testing
- [x] Develop simple chat system using python and c++
- [x] Create example TCP client/server files to reference for future code
- [ ] Develop protocol system to be used for communication
- [ ] Create example UI program to reference for future code
---
### DX / Docs
- [x] Establish link with GitHub
- [x] Create Licence for project
- [x] Begin Development of the README
- [ ] Finish Development of the README
- [ ] Finish demo.gif 
- [ ] Begin Development of requirements.txt
- [ ] Finish requirements.txt
---
