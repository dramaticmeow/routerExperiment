#include "lookuproute.h"
#include <stdint.h>

int insert_route(uint32_t ip4prefix,unsigned int prefixlen,char *ifname,unsigned int ifindex,uint32_t nexthopaddr)
{
	struct route* p = route_table;
	struct route* pre = NULL;
	while(p != NULL)
	{
		if(p->prefixlen == prefixlen && match_int(p->ip4prefix.s_addr, ip4prefix, prefixlen))
			return -1; // must first delete and then insert

		pre = p;
		p = p->next;
	}
	p = (struct route*) malloc(sizeof(struct route));
	if(pre != NULL)
		pre->next = p;
	p->next = NULL;
	p->ip4prefix.s_addr = ip4prefix;
	p->prefixlen = prefixlen;
	p->nexthop = (struct nexthop*) malloc(sizeof(struct nexthop));
	p->nexthop->next = NULL;
	p->nexthop->ifname = ifname;
	p->nexthop->ifindex = ifindex;
	p->nexthop->nexthopaddr.s_addr = nexthopaddr;
	return 0;
}

int lookup_route(struct in_addr dstaddr,struct nextaddr *nexthopinfo)
{
	struct route* hit = NULL;
	struct route* p = route_table;
	while(p != NULL)
	{
		if(match_ip(dstaddr, p->ip4prefix, p->prefixlen))
		{
			if(hit == NULL)
				hit = p;
			else if(p->prefixlen > hit->prefixlen)
				hit = p;
			
		}
		p = p->next;
	}

	if(hit == NULL)
		return -1;
	nexthopinfo->ifname = hit->nexthop->ifname;
	nexthopinfo->ipv4addr = hit->nexthop->nexthopaddr;
	nexthopinfo->prefixl = hit->nexthop->ifindex;
	return 0;
}

int delete_route(struct in_addr dstaddr,unsigned int prefixlen)
{
	struct route* p = route_table;
	struct route* pre = NULL;
	while(p != NULL)
	{
		if(p->prefixlen == prefixlen && match_ip(dstaddr, p->ip4prefix, prefixlen))
		{
			if(pre != NULL)
			{
				pre->next = p->next;
				return 0;
			}
			else
			{
				route_table = p->next;
				return 0;
			}
		}

		pre = p;
		p = p->next;
	}
	return -1;
}

