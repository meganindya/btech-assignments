import socket
import sys
from os import system


if __name__ == "__main__":
    system('clear')

    # create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect socket to the server's listening port
    server_address = ('localhost', 4200)
    print('connecting to %s port %s' % server_address, file=sys.stderr)
    sock.connect(server_address)

    try:
        # send data
        message = 'This is the message.  It will be repeated.'
        print('sending "%s"' % message, file=sys.stderr)
        sock.sendall(message.encode())

        # look for response
        amount_received = 0
        amount_expected = len(message)

        while amount_received < amount_expected:
            data = sock.recv(16).decode()
            amount_received += len(data)
            print('received "%s"' % data, file=sys.stderr)

    finally:
        print('closing socket', file=sys.stderr)
        sock.close()
