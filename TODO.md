## TODO

### Device (C++)
#### Core
- [x] Begin Development...
- [ ] `main.cpp` — entry point, boot sequence, start device loop
- [ ] `device.h/.cpp` — main device class, owns all components, runs main loop
#### Communication
- [ ] `tcp_client.h/.cpp` — socket logic, connect to server, send/recv, retry logic
- [x] `protocol.h/.cpp` — message framing, serialization/deserialization
#### Config
- [x] Design `layout.json` schema — component types, IDs, metadata
- [x] `layout.json` — first real device config (LEDs, buttons, sensors, motors)
#### Components
- [ ] `component.h/.cpp` — base class/interface all components inherit from
- [ ] `led.h/.cpp`
- [ ] `button.h/.cpp`
- [ ] `sensor.h/.cpp`
- [ ] `motor.h/.cpp`
#### Build
- [x] `CMakeLists.txt` — build config, link includes and sources
---

### Server (Python)
#### Core
- [ ] Begin Development...
- [ ] `main.py` — entry point, starts server, launches dashboard
- [ ] `tcp_server.py` — accepts connections, passes to session handler
- [ ] `device_session.py` — manages connected device state, parsed layout, socket
- [ ] `protocol.py` — mirrors device protocol, message parsing
#### Dashboard
- [ ] `app.py` — dashboard entry point, main window/app loop
- [ ] `ui_builder.py` — dynamically builds UI widgets from received layout.json
- [ ] `dashboard/components/` — individual UI widgets (LED indicator, sensor graph, button, motor control)
---

### Protocol (Shared Contract)
- [x] Define message framing (length-prefix vs delimiter)
- [x] Define message types: `HANDSHAKE`, `COMMAND`, `STATE_UPDATE`, `SENSOR_DATA`, `ACK`
- [x] Decide serialization format (JSON vs binary vs custom)
- [ ] Document protocol spec in `docs/`
---

### Testing
- [x] Develop simple chat system using Python and C++
- [x] Create example TCP client/server files to reference
- [ ] `mock_server.py` — test device handshake and protocol in isolation
- [ ] `mock_device.py` — test server/UI without C++ running
- [ ] `protocol_tests/` — unit tests for message framing and parsing
- [ ] Develop protocol system to be used for communication
- [ ] Create example UI program to reference for future code
---

### DX / Docs
- [x] Establish link with GitHub
- [x] Create licence for project
- [x] Begin development of the README
- [ ] Finish development of the README
- [ ] `demo.gif` — record and finish demo
- [ ] `requirements.txt` — begin and finish Python dependencies
- [ ] Document protocol spec
- [ ] Document `layout.json` schema
---