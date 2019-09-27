#include <stdio.h>
#include <libnet.h>
#include "headers.h"
#include <net/ethernet.h>
#include <netinet/ether.h>

// Decode Ethernet header
u_int decodeEthernet(const u_char *encodedHdr) {
    const struct ethernetHeader *ethHdr;
    ethHdr = (const struct ethernetHeader*) encodedHdr;

    struct ether_addr srcAddr;
    struct ether_addr destAddr;

    strncpy(srcAddr.ether_addr_octet, ethHdr->etherSrcAddr, sizeof(srcAddr.ether_addr_octet) / sizeof(u_char));
    strncpy(destAddr.ether_addr_octet, ethHdr->etherDestAddr, sizeof(destAddr.ether_addr_octet) / sizeof(u_char));

    printf("------------[ Ethernet Header ]------------\nSource MAC Address: %s\n", ether_ntoa(&srcAddr));
    printf("Destination MAC Address: %s\n-------------------------------------------\n", ether_ntoa(&destAddr));
    return ETHER_HEADER_LEN;
}

// Decode IP header
u_int decodeIp(const u_char *encodedHdr) {
    const struct ipHeader *ipHdr;
    ipHdr = (const struct ipHeader*) encodedHdr;

    char srcAddr[INET_ADDRSTRLEN];
    char destAddr[INET_ADDRSTRLEN];
    
    struct in_addr ipSrcAddr;
    struct in_addr ipDestAddr;

    ipSrcAddr.s_addr = ipHdr->ipSrcAddr;
    ipDestAddr.s_addr = ipHdr->ipDestAddr;

    inet_ntop(AF_INET, &(ipSrcAddr.s_addr), srcAddr, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ipDestAddr.s_addr), destAddr, INET_ADDRSTRLEN);

    printf("-----------[ IP Header ]-----------\nSource IP Address: %s\nDestination IP Address: %s\nID Number: %u\n-----------------------------------\n",
    srcAddr, destAddr, ntohs(ipHdr->ipId));
    return ipHdr->ipLength;
}

// Decode TCP header
        /* NOTE: Add flags */
u_int decodeTcp(const u_char *encodedHdr) {
    const struct tcpHeader *tcpHdr;
    u_int headerSize;
    
    // Parse TCP
    tcpHdr = (const struct tcpHeader*) encodedHdr;
    /*
        The TCP offset field describes the number of 32 bit words in the entire header.
        32 bits = 4 bytes.
        By multiplying the value of the TCP offset header by 4, we can get the size of the TCP header.
    */
    headerSize = 4 * tcpHdr->tcpOffset; 
    printf("-----------[ TCP Header ]-----------\nSource Port: %u\nDestination Port: %u\nSequence Number: %u\nAcknowledgement Number: %u\n-----------------------------------\n",
    ntohs(tcpHdr->tcpSrcPort), ntohs(tcpHdr->tcpDestPort), tcpHdr->tcpSeq, tcpHdr->tcpAck);
    return headerSize;
}