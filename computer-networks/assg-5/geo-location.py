# File: geo-location.py

# Author: Anindya Kundu <anindya.k22@outlook.com>
# Date: 2020-06-15

# Reference: https://docs.python.org/3/library/

"""
Finds the geographic loaction of a client connecting to this
server. Opens the location in a Google Map in default browser.

Functions:

- `_map_geo()`: maps geographic location of connecting client
        in Google Maps on default browser

How To Use This Module
======================
1. run this script using [python3 geo-location.py]
2. run client script from a different (non-private range) location
    using [python3 client.py]
"""


import socket
import sys
from os import system
import urllib
import json
import requests
import webbrowser


# use public range IP
host = "192.168.0.6"  # for demonstration only (will not work in private range)
port = 4200


def _map_geo(sock):
    """
    Accepts a client connecting to this server. Uses IP API to fetch
    information gathered from IP in JSON format. Print the data, and
    maps the location in Google Maps on default browser.

    Parameters:

    - `sock`: socket object
    """

    while True:
        # accept new connection
        conn, addr = sock.accept()

        # API to fetch geolocation of IP
        url = "http://ip-api.com/json/" + addr[0] + "?fields=61439"

        # parse JSON structure
        response = urllib.request.urlopen(url)
        resp_json = response.read().decode('utf-8')
        data = json.loads(resp_json)

        # print status, country,countryCode, region, regionName,
        # city, zip, lat, lon, timezone, isp, org, as, query
        for key in data:
            print(str(key)+": "+str(data[key]))

        # maps on Google Maps on default browser
        final_url = "https://www.google.com/maps/@" +\
            str(data["lat"]) + "," + str(data["lon"]) + ", 18.5z"
        webbrowser.open(final_url, new=2)


if __name__ == "__main__":
    """
    Attribute is __main__ when module is run as main program.
    """

    # clear console
    system('clear')

    # create TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # bind socket to the address and port
    server_address = (host, port)
    sock.bind(server_address)

    # listen on port
    sock.listen(5)

    try:
        # map geographic location
        _map_geo(sock)

    finally:
        # clean up connection
        print('\nclosing socket', file=sys.stderr)
        sock.close()
