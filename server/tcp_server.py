import socket
from protocol import receive_message, send_message
from device_session import DeviceSession

HOST = 'localhost'
PORT = 8080

def handle_connection(conn, addr):
    print(f"[Server] Connected by {addr}")

    message = receive_message(conn)
    if not message:
        print("[Server] No message received.")
        return

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