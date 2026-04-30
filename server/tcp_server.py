import socket
from protocol import receive_message, send_message
from device_session import DeviceSession

HOST = 'localhost'
PORT = 8080

def handle_connection(conn, addr):
    print(f"[Server] Connected by {addr}")

    # Receive handshake message
    message = receive_message(conn)
    if not message:
        print("[Server] No message received.")
        return

    # Process handshake
    if message["type"] == "HANDSHAKE":
        # create session from handshake
        session = DeviceSession(conn, addr, message)

        # send ACK
        send_message(conn, {
            "type": "HANDSHAKE_ACK",
            "payload": {
                "status": "ok"
            }
        })
        print("[Server] Handshake ACK sent")

        # print session info
        session.print_session()
    else:
        print(f"[Server] Unexpected message type: {message['type']}")
        return
    
    # main loop - send commands to device
    # main loop - listen for state updates
    print("\n[Server] Listening for state updates...")
    while True:
        message = receive_message(conn)
        if not message:
            print("[Server] Device disconnected.")
            break

        if message["type"] == "STATE_UPDATE":
            print(f"[Server] Received state update: {message}")
            component_id = message["payload"]["component_id"]
            state = message["payload"]["state"]
            session.update_component_state(component_id, state)
            print(f"[STATE] {component_id} -> {state}")

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()
        print(f"[Server] Listening on {HOST}:{PORT} ...")

        conn, addr = s.accept()
        with conn:
            handle_connection(conn, addr)

if __name__ == "__main__":
    main()