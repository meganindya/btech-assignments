import socket
import sys
from os import system


localIP    = "127.0.0.1"
localPort  = 4200
bufferSize = 1024


if __name__ == "__main__":
    system('clear')

    # create TCP/IP socket
    sock = socket.socket(family = socket.AF_INET, type = socket.SOCK_DGRAM)

    # bind socket to the address and port
    server_address = ('localhost', 4200)
    print('starting up on %s port %s' % server_address, file=sys.stderr)
    sock.bind(server_address)

    # listen for incoming connections
    sock.listen(1)

    while True:
        # wait for a connection
        print('server up and listening', file=sys.stderr)
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



msgFromServer       = "Hello UDP Client"
bytesToSend         = str.encode(msgFromServer)
# Create a datagram socket
UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
# Bind to address and ip
UDPServerSocket.bind((localIP, localPort))
print("UDP server up and listening")
# Listen for incoming datagrams
while(True):
    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
    message = bytesAddressPair[0]
    address = bytesAddressPair[1]
    clientMsg = "Message from Client:{}".format(message)
    clientIP  = "Client IP Address:{}".format(address)
    print(clientMsg)
    print(clientIP)
    # Sending a reply to client
    UDPServerSocket.sendto(bytesToSend, address)
