import threading

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        while True:
            conn, addr = s.accept()``
            thread = threading.Thread(target=message_handler, args=(conn, addr))
            thread.start()

