# File: tcp-client.py

# Author: Anindya Kundu <anindya.k22@outlook.com>
# Date: 2020-06-15

# Reference: https://docs.python.org/3/library/

"""
Connects to server which finds location of this client.

How To Use This Module
======================
1. run server script using [python3 geo-location.py]
2. run this script using [python3 client.py] from a non-private range
"""


import socket
import sys
from os import system


# use public range IP
host = "192.168.0.6"    ## for demonstration only (will not work in private range)
port = 4200


if __name__ == "__main__":
    """
    Attribute is __main__ when module is run as main program.
    """

    # clear console
    system('clear')

    # create TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect socket to the server's listening port
    server_address = (host, port)
    print('connecting to %s port %s\n' % server_address, file=sys.stderr)
    sock.connect(server_address)

    # clean up connection
    print('closing socket', file=sys.stderr)
    sock.close()
