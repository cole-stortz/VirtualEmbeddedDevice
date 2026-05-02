## TODO

### Device (C++)
#### Core
- [x] Begin Development...
- [x] `main.cpp` — entry point, boot sequence, start device loop
- [ ] `device.h/.cpp` — main device class, owns all components, runs main loop
- [x] `program.h/.cpp` — main program to write embedded like code into.
#### Communication
- [x] `tcp_client.h/.cpp` — socket logic, connect to server, send/recv, retry logic
- [x] `protocol.h/.cpp` — message framing, serialization/deserialization
#### Config
- [x] Design `layout.json` schema — component types, IDs, metadata
- [x] `layout.json` — first real device config (LEDs, buttons, sensors, motors)
#### Components
- [x] `component.h/.cpp` — base class/interface all components inherit from
- [x] `led.h/.cpp`
- [ ] `button.h/.cpp`
- [x] `sensor.h/.cpp`
- [ ] `motor.h/.cpp`
#### Build
- [x] `CMakeLists.txt` — build config, link includes and sources
---

### Server (Python)
#### Core
- [x] Begin Development...
- [ ] `main.py` — entry point, starts server, launches dashboard
- [x] `tcp_server.py` — accepts connections, passes to session handler
- [x] `device_session.py` — manages connected device state, parsed layout, socket
- [x] `protocol.py` — mirrors device protocol, message parsing
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
- [x] `test_server.py` — test device handshake and protocol in isolation
- [x] `test_device.py/.cpp` — test server/UI without C++ running
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