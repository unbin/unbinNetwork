#ifndef NET_TOOLS_H
#define NET_TOOLS_H

#include <libnet.h>

u_char decodeEthernet(const u_char*);
u_char decodeIp(const u_char*);
u_char decodeTcp(const u_char*);

#endif

