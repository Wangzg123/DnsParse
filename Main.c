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

	if(DNSSend(argv[1],dnscheck) < 0)
	{
		debug_info("DNSSend() error");
		exit(-1);
	}
	DNSRecv(dnscheck);
	exit(0);
}



