#include "checksum.h"

int check_sum(unsigned short *iphd,int len,unsigned short checksum)
{
   unsigned int cksum = 0;
   int i;
   for(i = 1; i <= 10; i++){
   	cksum += *iphd++;
   }
   cksum = (cksum >> 16) + (cksum & 0xffff);
   cksum = (cksum >> 16) + (cksum & 0xffff);
   unsigned short tmp = (unsigned short)cksum;
   if(~tmp == 0)
   	return 1;
   else
   	return 0;
}
unsigned short count_check_sum(unsigned short *iphd)
{
    *(iphd + 5) = 0;
    *(unsigned char*)(iphd+4)--;
   unsigned int cksum = 0;
   int i;
   for(i = 1; i <= 10; i++){
   	cksum += *(iphd+i-1);
   }
   cksum = (cksum >> 16) + (cksum & 0xffff);
   cksum = (cksum >> 16) + (cksum & 0xffff);
   *(iphd+5) = ~((unsigned short)cksum);
   return *(iphd+5);
}
