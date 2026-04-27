import threading
import socket

HOST = 'localhost'
PORT = 12345

def definition_of_something():
    pass

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        while True:
            conn, addr = s.accept()
            thread = threading.Thread(target=definition_of_something, args=(conn, addr))
            thread.start()

