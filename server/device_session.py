class DeviceSession:
    def __init__(self, conn, addr, layout: dict):
        self.conn = conn
        self.addr = addr
        self.device_name = layout["payload"]["device_name"]
        self.version = layout["payload"]["version"]
        self.components = layout["payload"]["layout"]["components"]

    def get_component(self, component_id: str) -> dict:
        for component in self.components:
            if component["id"] == component_id:
                return component
        return None
    
    def update_component_state(self, component_id: str, state: dict):
        component = self.get_component(component_id)
        if component:
            component["state"].update(state)
    
    def print_session(self):
        print(f"[Session] Device: {self.device_name} v{self.version}")
        print(f"[Session] Address: {self.addr}")
        print(f"[Session] Components:")
        for component in self.components:
            print(f"  - [{component['type']}] {component['id']} | {component['label']} | state: {component['state']}")