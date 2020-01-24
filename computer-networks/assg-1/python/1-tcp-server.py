import socket
import sys
from os import system


if __name__ == "__main__":
    system('clear')

    # create TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # bind socket to the address and port
    server_address = ('localhost', 4200)
    print('starting up on %s port %s' % server_address, file=sys.stderr)
    sock.bind(server_address)

    # listen for incoming connections
    sock.listen(1)

    while True:
        # wait for a connection
        print('waiting for a connection', file=sys.stderr)
        connection, client_address = sock.accept()

        try:
            print('connection from', client_address, file=sys.stderr)

            # receive data in small chunks and retransmit it
            while True:
                data = connection.recv(16).decode()
                print('received "%s"' % data, file=sys.stderr)
                if data:
                    print('sending data back to the client', file=sys.stderr)
                    connection.sendall(data.encode())
                else:
                    print('no more data from', client_address, file=sys.stderr)
                    break

        finally:
            # clean up connection
            connection.close()
