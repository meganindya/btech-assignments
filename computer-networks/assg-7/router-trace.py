# File: router-trace.py

# Author: Anindya Kundu <anindya.k22@outlook.com>
# Date: 2020-06-15

# Reference: https://github.com/dnaeon/pytraceroute

"""
A simple traceroute program.

Traces the visited servers and time per hop on the way to a destination server.

Functions:

- `_create_receiver()`: creates a receiver socket
- `_create_sender()`: creates a sender socket
- `_run()`: runs the tracer

How To Use This Module
======================
run this script using [python3 router-trace.py <destination IP>]
"""


from os import system
import sys
import socket
import random
import struct
import time


def _create_receiver(port):
    """
    Creates a receiver socket.

    Returns:
        A socket instance

    Raises:
        IOError
    """

    # raw socket
    sock = socket.socket(
        family=socket.AF_INET,
        type=socket.SOCK_RAW,
        proto=socket.IPPROTO_ICMP
    )

    timeout = struct.pack("ll", 5, 0)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVTIMEO, timeout)

    try:
        sock.bind(('', port))
    except socket.error as e:
        raise IOError('receiver socket bind failed: {}'.format(e))

    return sock


def _create_sender(ttl):
    """
    Creates a sender socket.

    Returns:
        A socket instance
    """

    # UDP socket
    sock = socket.socket(
        family=socket.AF_INET,
        type=socket.SOCK_DGRAM,
        proto=socket.IPPROTO_UDP
    )

    sock.setsockopt(socket.SOL_IP, socket.IP_TTL, ttl)

    return sock


def _run(dst):
    """
    Runs the tracer.

    Raises:
        IOError
    """

    hops = 30       # maximum number of hops
    ttl = hops      # initial time to live
    port = 43154    # sender port number


    # get IP from domain
    try:
        dst_ip = socket.gethostbyname(dst)
    except socket.error as e:
        raise IOError('failed to resolve {}: {}'.format(dst, e))


    text = 'traceroute to {} ({}), {} hops max'.format(
        dst,
        dst_ip,
        hops
    )

    print(text)


    # hop loop
    while True:
        receiver = _create_receiver(port)
        sender = _create_sender(hops - ttl + 1)

        # start time for current hop
        start_time = time.time()

        sender.sendto(b'', (dst, port))

        addr = None
        try:
            # receive packet and calculate end time
            data, addr = receiver.recvfrom(1024)
            end_time = time.time()
        except socket.error:
            pass
        finally:
            receiver.close()
            sender.close()

        # print router/server address
        if addr:
            time_cost = round((end_time - start_time) * 1000, 2)
            print(
                '{:<4} {} \t{} ms'.format(hops - ttl + 1, addr[0], time_cost)
            )
            if addr[0] == dst_ip:
                break
        else:
            print('{:<4} *'.format(hops - ttl + 1))

        # decrement ttl at end of each hop
        ttl -= 1

        if ttl == 0:
            break


if __name__ == '__main__':
    system("clear")

    if len(sys.argv) == 1:
        print("usage: python3 {} <destination IP>".format(sys.argv[0]))
        exit()

    # run trace for destination
    dst = sys.argv[1]
    _run(dst)
