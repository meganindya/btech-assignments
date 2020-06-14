/**
 * @file Raw socket headers program
 * @brief This program defines a raw socket and receives a packet. It then
 * extracts the Ethernet, IP, and TCP headers and prints them to stdout.
 *
 * @ref https://pubs.opengroup.org/onlinepubs/7908799/
 * @ref https://opensourceforu.com/2015/03/a-guide-to-using-raw-sockets/
 * @ref http://ttcplinux.sourceforge.net/documents/one/structure/tcphdr.html
 * @ref https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
 *
 * ****************************************************************************
 * compile using [cc -pack_headers 1-raw-packet-headers.c]
 * run using [./pack_headers]
 * ****************************************************************************
 *
 * @author Anindya Kundu <anindya.k22@outlook.com>
 * @date 2020-06-14
*/

#define _DEFAULT_SOURCE

#include <stdio.h>              /** @include standard buffered input/output */
#include <stdlib.h>             /** @include standard library definitions */
#include <sys/socket.h>         /** @include main sockets header */
#include <arpa/inet.h>          /** @include definitions for internet operations */
#include <netinet/if_ether.h>   /** @include ethernet (MAC) addresses */
#include <netinet/ip.h>         /** @include definitions for internet protocol version 4 */
#include <netinet/tcp.h>        /** @include definitions for the internet Transmission Control Protocol (TCP) */
#include <string.h>             /** @include string operations */
#include <unistd.h>             /** @include standard symbolic constants and types */

/**
 * Main function.
 *
 * @returns exit status
 */
int main(void)
{
    /** clear terminal (stdlib.h) */
    system("clear"); // unix-like
    // system("cls");   // cmd/powershell

    /** raw socket file descriptor */
    int sockfd_r = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (sockfd_r == -1)
    {
        perror("-- socket creation failed, error");
        exit(1);
    }
    else
    {
        printf("-- socket created successfully\n");
    }

    /** stores packet contents */
    unsigned char *buffer = (unsigned char *)malloc(65536);
    memset(buffer, 0, 65536);   // clear (set all to 0)

    /** socket address descriptor */
    struct sockaddr saddr;
    /** socket address length */
    socklen_t saddr_len = (socklen_t)sizeof(saddr);

    // receive a network packet and copy it to buffer
    ssize_t buflen = recvfrom(
        sockfd_r, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_len
    );
    
    if (buflen < 0)
    {
        perror("-- reading failed");
        exit(1);
    }

    /** stores ethernet header pointer */
    struct ethhdr *eth = (struct ethhdr *)(buffer);
    printf("\nEthernet Header\n===============\n");
    printf(
        "|- Source Address\t: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
        eth->h_source[0],
        eth->h_source[1],
        eth->h_source[2],
        eth->h_source[3],
        eth->h_source[4],
        eth->h_source[5]);
    printf(
        "|- Destination Address\t: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
        eth->h_dest[0],
        eth->h_dest[1],
        eth->h_dest[2],
        eth->h_dest[3],
        eth->h_dest[4],
        eth->h_dest[5]
    );
    printf("|- Protocol\t\t: %d\n", eth->h_proto);

    /** stores IP header pointer */
    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    /** stores actual size of IP header */
    unsigned short iphdrlen = ip->ihl * 4;

    /** address descriptor for source */
    struct sockaddr_in source;
    memset(&source, 0, sizeof(source)); // clear (set all to 0)
    source.sin_addr.s_addr = ip->saddr; // size of source

    /** address descriptor for destination */
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));     // clear (set all to 0)
    dest.sin_addr.s_addr = ip->daddr;   // size of destination

    printf("\nIP Header\n=========\n");
    printf("|- Version\t\t\t: %d\n", (unsigned int)ip->version);
    printf(
        "|- Internet Header Length\t: %d DWORDS or %d Bytes\n",
        (unsigned int)ip->ihl,
        ((unsigned int)(ip->ihl)) * 4
    );
    printf("|- Type Of Service\t\t: %d\n", (unsigned int)ip->tos);
    printf("|- Total Length\t\t\t: %d Bytes\n", ntohs(ip->tot_len));
    printf("|- Identification\t\t: %d\n", ntohs(ip->id));
    printf("|- Time To Live\t\t\t: %d\n", (unsigned int)ip->ttl);
    printf("|- Protocol\t\t\t: %d\n", (unsigned int)ip->protocol);
    printf("|- Header Checksum\t\t: %d\n", ntohs(ip->check));
    printf("|- Source IP\t\t\t: %s\n", inet_ntoa(source.sin_addr));
    printf("|- Destination IP\t\t: %s\n", inet_ntoa(dest.sin_addr));

    /* stores TCP header pointer */
    struct tcphdr *tcp = (struct tcphdr *)(buffer + iphdrlen + sizeof(struct ethhdr));

    printf("\nTCP Header\n==========\n");
    printf("|- Source Port\t\t\t: %d\n" , ntohs(tcp->source));
    printf("|- Destination Port\t\t: %d\n" , ntohs(tcp->dest));
    printf("|- Sequence Number\t\t: %d\n" , ntohs(tcp->seq));
    printf("|- Acknowledge Sequence\t\t: %d\n", ntohs(tcp->ack_seq));
    printf(
        "|- TCP Header Length\t\t: %d DWORDS or %d Bytes\n",
        (unsigned int)sizeof(tcp),
        ((unsigned int)sizeof(tcp)) * 4
    );
    printf("   |- Urgent Flag\t\t: %d\n", (unsigned int)tcp->urg);
    printf("   |- Acknowledgement Flag\t: %d\n", (unsigned int)tcp->ack);
    printf("   |- Push Flag\t\t\t: %d\n", (unsigned int)tcp->psh);
    printf("   |- Reset Flag\t\t: %d\n", (unsigned int)tcp->rst);
    printf("   |- Synchronize Flag\t\t: %d\n", (unsigned int)tcp->syn);
    printf("   |- Finish Flag\t\t: %d\n", (unsigned int)tcp->fin);
    printf("|- Window Size\t\t\t: %d\n", ntohs(tcp->window));
    printf("|- Checksum\t\t\t: %d\n", ntohs(tcp->check));
    printf("|- Urgent Pointer\t\t: %d\n", ntohs(tcp->urg_ptr));

    close(sockfd_r);
    printf("\n-- socket closed\n");
}
