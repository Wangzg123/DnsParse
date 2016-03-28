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
		printf("error input\n");
		exit(-1);
	}

	DNSInfo *dnscheck;
	dnscheck = malloc(sizeof(DNSInfo));

	if(DNSSend(argv[1],dnscheck) == 0)
	{
		printf("DNSSend() error\n");
		exit(-1);
	}

	if(DNSRecv(dnscheck) == 0)
	{
		printf("DNSRecv() error\n");
		exit(-1);
	}

	free(dnscheck);
	exit(0);
}



