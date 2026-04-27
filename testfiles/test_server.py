import socket


HOST = 'localhost'
PORT = 8080

def message_handler(conn, addr):
    while True:
        # Wait for a message from the client
        data = conn.recv(1024)
        if not data:
            print("[Server] Client disconnected.")
            break

        print(f"[Client]: {data.decode()}")

        # Send a reply
        reply = input("[You (server)]: ")
        conn.sendall(reply.encode())

        if reply.lower() in ("quit", "exit"):
            print("[Server] Closing connection.")
            break

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()
        print(f"[Server] Listening on {HOST}:{PORT} ...")

        conn, addr = s.accept()
        with conn:
            print(f"[Server] Connected by {addr}\n")
            message_handler(conn, addr)
            

if __name__ == "__main__":
    main()