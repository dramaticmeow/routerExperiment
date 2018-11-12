#ifndef __FIND__
#define __FIND__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

struct route
{
    struct route *next;
    struct in_addr ip4prefix;
	unsigned int prefixlen;
    struct nexthop *nexthop;
};

struct nexthop
{
   struct nexthop *next;
   char *ifname;
   unsigned int ifindex;//zlw ifindex2ifname()获取出接�?   // Nexthop address 
   struct in_addr nexthopaddr;
};

struct nextaddr
{
   char *ifname;
   struct in_addr ipv4addr;
   unsigned int prefixl;
};

struct route *route_table; 
int insert_route(uint32_t ip4prefix,unsigned int prefixlen,char *ifname,unsigned int ifindex,uint32_t nexthopaddr);
int lookup_route(struct in_addr dstaddr,struct nextaddr *nexthopinfo);
int delete_route(struct in_addr dstaddr,unsigned int prefixlen);
inline bool match_ip(struct in_addr a, struct in_addr b, unsigned int prefixlen)
{
  return ntohl(a.s_addr) >> (32-prefixlen) == ntohl(b.s_addr) >> (32-prefixlen);
}
inline bool match_int(uint32_t a, uint32_t b, unsigned int prefixlen)
{
  return ntohl(a) >> (32-prefixlen) == ntohl(b) >> (32-prefixlen);
}
#endif
