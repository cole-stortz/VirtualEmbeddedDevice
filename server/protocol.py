import socket
import struct
import json

# This module defines the protocol for sending and receiving messages between the server and client.
def send_message(sock: socket.socket, data: dict):
    message = json.dumps(data).encode('utf-8')
    length = struct.pack('>I', len(message))
    sock.sendall(length + message)

# This function reads a message from the socket, first reading the 4-byte length 
# header, then reading the message itself.
def receive_message(sock: socket.socket) -> dict:
    # read exactly 4 bytes for the length header
    header = b''
    while len(header) < 4:
        chunk = sock.recv(4 - len(header))
        if not chunk:
            return None
        header += chunk
    
    # unpack the length header to get the message length
    message_length = struct.unpack('>I', header)[0]

    # read that many bytes for the message
    message = b''
    while len(message) < message_length:
        chunk = sock.recv(message_length - len(message))
        if not chunk:
            return None
        message += chunk
        
    return json.loads(message.decode('utf-8'))