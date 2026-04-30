import socket
from protocol import send_message, receive_message

HOST = 'localhost'
PORT = 8080

# This is a simple TCP server that listens for incoming connections and handles a handshake message from the client.
def handle_client(conn, addr):
    print(f"[Server] Connected by {addr}")

    # wait for handshake message
    message = receive_message(conn)
    if not message:
        print(f"[Server] No handshake recieved")
        return
    
    # handle handshake message
    if message["type"] == "HANDSHAKE":
        print(f"[Server] Handshake received from: {message['payload']['device_name']}")
        print(f"[Server] Version: {message['payload']['version']}")
        print(f"[Server] Components:")
        for component in message["payload"]["layout"]["components"]:
            print(f"  - [{component['type']}] {component['id']} | {component['label']}")

        # send handshake response
        send_message(conn, {
            "type": "HANDSHAKE_ACK",
            "payload": {
                "status": "ok"
            }
        })

        print("[Server] Handshake ACK sent\n")
    else:
        print(f"[Server] Unexpected message type: {message['type']}")

def main():
    # Start the TCP server
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print(f"[Server] Listening on {HOST}:{PORT}...")

        # Accept incoming connections and handle them
        conn, addr = s.accept()
        with conn:
            handle_client(conn, addr)

if __name__ == "__main__":
    main()