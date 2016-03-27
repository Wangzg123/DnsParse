/*
 * MyDNS.h
 *
 *  Created on: 2016年3月25日
 *      Author: apple
 */

#ifndef MYDNS_H_
#define MYDNS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>

#define debug_info(fmt, ... ) \
	do{Nowtime();printf("[%s][%d]: "fmt"\n",__func__,__LINE__,##__VA_ARGS__);}while(0)

typedef struct _DNSInfo
{
	uint8_t  	Domain[30];
	uint32_t 	Domainlen;
	uint32_t 	sockfd;
	uint16_t 	randid;
}DNSInfo;

typedef struct _IPInfo
{
	struct _IPInfo *next;
	struct _IPInfo *prev;

	uint8_t IP[4];
}IPInfo;

uint32_t DNSSend(char *Domain,DNSInfo *dns);
uint32_t DNSRecv(DNSInfo *dns,IPInfo *ip);

#endif /* MYDNS_H_ */
