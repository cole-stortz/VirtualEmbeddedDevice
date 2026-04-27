import socket

HOST = 'localhost'
PORT = 8080

def message_handler(s):
    while True:
        # Client sends first
        message = input("[You (client)]: ")
        s.sendall(message.encode())

        if message.lower() in ("quit", "exit"):
            print("[Client] Closing connection.")
            break

        # Wait for server reply
        data = s.recv(1024)
        if not data:
            print("[Client] Server disconnected.")
            break

        print(f"[Server]: {data.decode()}")

        if data.decode().lower() in ("quit", "exit"):
            print("[Client] Server ended the chat.")
            break

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print(f"[Client] Connected to {HOST}:{PORT}\n")
        
        message_handler(s)

        

if __name__ == "__main__":
    main()