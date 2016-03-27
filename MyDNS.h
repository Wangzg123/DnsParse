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
	do{if(0){Nowtime();printf("[%s][%d]: "fmt"\n",__func__,__LINE__,##__VA_ARGS__);}}while(0)

#define debug_info1(fmt, ... ) \
	do{if(1){Nowtime();printf("[%s][%d]: "fmt"\n",__func__,__LINE__,##__VA_ARGS__);}}while(0)

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

	uint8_t *IP;
}IPInfo;

uint32_t DNSSend(uint8_t *Domain,DNSInfo *dns);
IPInfo *DNSRecv(DNSInfo *dns,IPInfo *ip);

#endif /* MYDNS_H_ */
