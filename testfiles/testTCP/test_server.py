import socket
import struct

HOST = 'localhost'
PORT = 8080

def send_message(socket, message):
    encode = message.encode('utf-8')
    header = struct.pack('>I', len(encode))  # 4-byte big-endian length
    socket.sendall(header + encode)

def recv_message(socket):
    # read exactly 4 bytes for the length header
    header = b''
    while len(header) < 4:
        chunk = socket.recv(4 - len(header))
        if not chunk:
            return None
        header += chunk
    
    message_length = struct.unpack('>I', header)[0]
    print(f"[DEBUG] Raw header bytes: {header.hex()} Message length: {message_length}")

    # read exactly that many bytes for the message
    message_data = b''
    while len(message_data) < message_length:
        chunk = socket.recv(message_length - len(message_data))
        if not chunk:
            return None
        message_data += chunk
    
    return message_data.decode('utf-8')



def message_handler(conn, addr):
    while True:
        # Wait for a message from the client
        data = recv_message(conn)
        if not data:
            print("[Server] Client disconnected.")
            return

        print(f"[Client]: {data}")

        # Send a reply
        reply = input("[You (server)]: ")
        send_message(conn, reply)

        if reply.lower() in ("quit", "exit"):
            print("[Server] Closing connection.")
            return

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