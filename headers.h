#ifndef HEADERS_H
#define HEADERS_H

#define ETHER_ADDR_LEN 6
#define ETHER_HEADER_LEN 14

struct ethernetHeader {
    unsigned char etherDestAddr[ETHER_ADDR_LEN]; // Destination MAC address
    unsigned char etherSrcAddr[ETHER_ADDR_LEN]; // Source MAC address
    unsigned short etherType; // Type of Ethernet packet
};

struct ipHeader {
    unsigned char ipVersionAndIhl; // Version and header length
    unsigned char ipTos; // Type of service
    unsigned short ipLength; // Total length
    unsigned short ipId; // Identification number
    unsigned short ipFragOffset; // Fragment offset and flags
    unsigned char ipTtl; // Time to live
    unsigned char ipType; // Protocol type
    unsigned short ipChecksum; // Checksum
    unsigned int ipSrcAddr; // Source address
    unsigned int ipDestAddr; // Destination address
};

struct tcpHeader {
    unsigned short tcpSrcPort; // Source port
    unsigned short tcpDestPort; // Destination port
    unsigned int tcpSeq; // Sequence number
    unsigned int tcpAck; // Acknowledgement number
    /*
    #if __BYTE_ORDER == __LITTLE_ENDIAN
        unsigned char reserved:4; // Reserved
        unsigned char tcpOffset:4; // Data offset
    #endif
    #if __BYTE_ORDER == __BIG_ENDIAN
        unsigned char tcpOffset:4; // Data offset
        unsigned char reserved:4; // Reserved
    #endif
    */
    // Assuming Little Endian architecture
    unsigned char reserved:4; // Reserved
    unsigned char tcpOffset:4; // Data offset (used to calculate size of variable length TCP header)
    unsigned char tcpFlags; // 6 control bits, 2 bits for reserved field
    #define TCP_FIN 0x01
    #define TCP_SYN 0x02
    #define TCP_RST 0x04
    #define TCP_PUSH 0x08
    #define TCP_ACK 0x10
    #define TCP_URG 0x20
    unsigned short tcpWindow; // Window size
    unsigned short tcpChecksum; // Checksum
    unsigned short tcpUrgent; // Urgent pointer
};

#endif