/**
 * @file Wake on LAN
 * @brief This program sends a magic packet to the NIC of a given MAC and/or
 * broadcast IP address which turns on the system.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://users.isc.tuc.gr/~agrammatopoulos/projects/WakeOnLan/index.html
 *
 * ****************************************************************************
 * compile using [ cc -o wol 2-wake-on-lan.c ]
 * run using [ ./wol <mac address> [<broadcast address>] ]
 * ****************************************************************************
 *
 * @author Anindya Kundu <anindya.k22@outlook.com>
 * @date 2020-06-14
*/

#include <stdio.h>      /** @include standard buffered input/output */
#include <stdlib.h>     /** @include standard library definitions */
#include <sys/socket.h> /** @include main sockets header */
#include <arpa/inet.h>  /** @include definitions for internet operations */
#include <netinet/in.h> /** @include internet address family */
#include <errno.h>      /** @include system error numbers */
#include <string.h>     /** @include string operations */

/** declaration of magic packet creating function */
void createMagicPacket(unsigned char [], unsigned int []);

/**
 * Main function.
 *
 * @param argc - command line arguments' count
 * @param argv - command line arguments
 * @returns exit status
 */
int main(int argc, const char *argv[])
{
    /** default broadcast address */
    char broadcastAddress[16] = "192.168.0.255";
    /** packet buffer */
    unsigned char packet[102];
    /** MAC address */
    unsigned int mac[6];
    /** broadcast set flag */
    int broadcast = 1;

    /** UDP socket file descriptor */
    int udpSocket;
    /** client socket address descriptor */
    struct sockaddr_in udpClient;
    /** server socket address descriptor */
    struct sockaddr_in udpServer;

    // if missing arguments
    if (argc < 2)
    {
        perror("usage: ./wol <mac address> [<broadcast address>]\n");
        exit(EXIT_FAILURE);
    }

    int _temp;

    // parse MAC Address
    _temp = sscanf(
        argv[1],
        "%x:%x:%x:%x:%x:%x",
        &(mac[0]),
        &(mac[1]),
        &(mac[2]),
        &(mac[3]),
        &(mac[4]),
        &(mac[5])
    );
    if (_temp != 6)
    {
        perror("invalid MAC address was given\n");
        exit(EXIT_FAILURE);
    }

    printf(
        "\nPacket destination: %02hhx:%02x:%02x:%02x:%02x:%02x\n",
        mac[0],
        mac[1],
        mac[2],
        mac[3],
        mac[4],
        mac[5]
    );

    // if a broadcast address is passed too
    if (argc > 2)
    {
        // parse broadcast address
        _temp = sscanf(argv[2], "%d.%d.%d.%d", &_temp, &_temp, &_temp, &_temp);
        if (_temp == 4)
        {
            // copy broadcast address
            strcpy(broadcastAddress, argv[2]);
        }
    }

    printf("\nBroadcast address: %s\n", broadcastAddress);

    // create magic packet
    createMagicPacket(packet, mac);

    // setup broadcast socket
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (
        setsockopt(
            udpSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)
        ) == -1
    )
    {
        perror("failed to setup a broadcast socket.\n");
        exit(EXIT_FAILURE);
    }

    // set parameters
    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;

    // bind socket
    bind(udpSocket, (struct sockaddr *)&udpClient, sizeof(udpClient));

    // set server end point (broadcast address)
    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr(broadcastAddress);
    udpServer.sin_port = htons(9);

    // send the packet
    sendto(
        udpSocket,
        &packet,
        sizeof(unsigned char) * 102,
        0,
        (struct sockaddr *)&udpServer,
        sizeof(udpServer)
    );
    printf("\n-- Wake Up packet sent\n");

    exit(EXIT_SUCCESS);
}

/**
 * Creates Magic Packets for a MAC.
 *
 * @param packet packet array
 * @param macAddress MAC address of target system
 */
void createMagicPacket(unsigned char packet[], unsigned int macAddress[])
{
    // Mac Address Variable
    unsigned char mac[6];

    // 6 x 0xFF on start of packet
    for (int i = 0; i < 6; i++)
    {
        packet[i] = 0xFF;
        mac[i] = macAddress[i];
    }

    // Rest of the packet is MAC address of the system
    for (int i = 1; i <= 16; i++)
    {
        memcpy(&packet[i * 6], &mac, 6 * sizeof(unsigned char));
    }
}
