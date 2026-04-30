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
    print("\n[Server] Enter commands to send to device (type quit to exit):")
    while True:
        component_id = input("Component ID: ")
        if component_id.lower() == "quit":
            print("[Server] Closing connection.")
            break
        action = input("Action: ")
        send_message(conn, {
            "type": "COMMAND",
            "payload": {
                "component_id": component_id,
                "action": action,
                "params": {"on": True}  # hardcoded for now just to test
            }
        })

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