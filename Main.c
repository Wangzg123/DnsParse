/*
 * Main.c
 *
 *  Created on: 2016年3月25日
 *      Author: apple
 */
#include "MyDNS.h"

int main(int argc,char **argv)
{
	if(argc != 2)
	{
		debug_info("error input");
		exit(-1);
	}
	DNSInfo *dnscheck;
	IPInfo *ip;
	dnscheck = malloc(sizeof(DNSInfo));
	ip = malloc(sizeof(IPInfo));
	ip->IP = "iii";
	ip->next = NULL;

	if(DNSSend(argv[1],dnscheck) < 0)
	{
		debug_info("DNSSend() error");
		exit(-1);
	}

	if(DNSRecv(dnscheck,ip) < 0)
	{
		debug_info("DNSRecv() error");
		exit(-1);
	}

	free(dnscheck);

	while(ip->next != NULL)
	{
		printf("ip = %s\n",ip->IP);
		ip = ip->next;
	}
	printf("ip = %s %s ",ip->IP,ip->next->IP);

	exit(0);
}



