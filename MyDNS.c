/*
 * MyDNS.c
 *
 *  Created on: 2016年3月25日
 *      Author: apple
 */
#include "MyDNS.h"

void Nowtime()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	struct tm *p;
	p = gmtime((time_t *)&tv.tv_sec);
	printf("[%02d:%02d:%02d.%06ld] ",(p->tm_hour+8)%24, p->tm_min, p->tm_sec, tv.tv_usec);
}

int32_t UdpOpenNoBlock()
{
	int32_t ret = -1;
	int32_t sockfd;
	int32_t flags;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		debug_info("socker() error");
		return ret;
	}
	flags = fcntl(sockfd,F_GETFL,0);
	flags |= O_NONBLOCK;
	if(fcntl(sockfd,F_SETFL,flags) < 0)
	{
		debug_info("fcntl() error");
		return ret;
	}
	ret = sockfd;
	return ret;
}
int32_t UdpSend(int32_t sockfd,char *buffer,int32_t len,char *Domain,int32_t Port)
{
	int sendlen = -1;
	struct sockaddr_in sockaddr;
	bzero(&sockaddr,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = Port;
	inet_pton(AF_INET,Domain,&sockaddr.sin_addr);

	sendlen = sendto(sockfd,buffer,len,0,(struct sockaddr *)&sockaddr,sizeof(sockaddr));
	if(sendlen <= 0)
		debug_info("sendto error");

	return sendlen;
}

/* = 0 no data to recv
 * > 0 return recvlen
 * < 0 sockfd error or timeout must reboot socket 	 */
int32_t UdpRecv(int32_t sockfd,char *buffer,int32_t len,int32_t mstimeout)
{
	int32_t recvlen = 0;
	struct sockaddr_in sockaddr;
	bzero(&sockaddr,sizeof(sockaddr));
	socklen_t socklen = sizeof(sockaddr);
	fd_set readfd;
	struct timeval tv;
	struct timespec ts;
	tv.tv_sec = mstimeout / 1000;
	tv.tv_usec = mstimeout % 1000 * 1000;

	FD_ZERO(&readfd);
	FD_SET(sockfd,&readfd);

	if(select(sockfd + 1,&readfd,NULL,NULL,&tv) > 0)
	{
		if(FD_ISSET(sockfd,&readfd))
		{
			recvlen = recvfrom(sockfd,buffer,len,0,(struct sockaddr *)&sockaddr,&socklen);
			if(recvlen > 0)
				return recvlen;
			if(recvlen < 0)
				debug_info("recvfrom error");
		}
	}
	if(recvlen == 0)
		debug_info("There is no data to read");
	return recvlen;
}

int32_t DNSSend(char *Domain,DNSInfo *dns)
{
	DNSInfo *dns_info = dns;
	int32_t ret = -1;
	int32_t i,j = 0,Position = 0;
	int32_t sendlen;

	char buffer[256];
	int16_t *randbuff = NULL;
	randbuff = (int16_t *)buffer;

	//dns_info->Domain = Domain;
	strncpy(dns_info->Domain,Domain,strlen(Domain) + 1);
	dns_info->Domainlen = strlen(dns_info->Domain);


	randbuff[0] = rand();						//ID
	dns_info->randid = randbuff[0];

	Position ++;
	Position ++;
	buffer[Position++] = 0x01;					//Flags
	buffer[Position++] = 0x00;					//Flags 			0x0100

	buffer[Position++] = 0x00;					//Questions;
	buffer[Position++] = 0x01;					//Questions;		0x0001

	buffer[Position++] = 0x00;					//Answer RRs;
	buffer[Position++] = 0x00;					//Answer RRs;		0x0000

	buffer[Position++] = 0x00;					//Authority RRs;
	buffer[Position++] = 0x00;					//Authority RRs;	0x0000

	buffer[Position++] = 0x00;					//Additional RRs;
	buffer[Position++] = 0x00;					//Additional RRs;	0x0000

	/***************************** Queries *******************************/
	for(i = 0;i < dns_info->Domainlen; i ++)
	{
		if(dns_info->Domain[i] == '.')
		{
			buffer[Position] = j;
			Position += j + 1;
			j = 0;
		}
		else
		{
			buffer[12 + i + 1] = Domain[i];
			j++;
		}
	}
	buffer[Position] = j;
	Position += j + 1;
	buffer[Position++] = 0x00;					//end Queries

	buffer[Position++] = 0x00;					//Type
	buffer[Position++] = 0x01;					//Type

	buffer[Position++] = 0x00;					//Class
	buffer[Position++] = 0x01;					//Class

	/*************** debug *****************
	for(i = 0; i < Position; i++)
	{
		printf("%d ",buffer[i]);
	}
	printf("\n");
	for(i = 0; i < Position; i++)
	{
		printf("%c ",buffer[i]);
	}
	printf("\n");
	****************************************/

	dns_info->sockfd = UdpOpenNoBlock();
	if(dns->sockfd < 0)
		return ret;

	sendlen = UdpSend(dns_info->sockfd,buffer,Position,"8.8.8.8",53);
	debug_info("sendlen = %d",sendlen);
	if(sendlen != Position)
		return ret;
	return sendlen;
}

int32_t DNSRecv(DNSInfo *dns)
{
	int32_t ret = -1;
	char recvbuf[512];
	int32_t recvlen;
	DNSInfo *dns_info = dns;
	recvlen = UdpRecv(dns_info->sockfd,recvbuf,512,0);
	if(recvlen <= 0)
		return ret;
	int16_t *buffer = NULL;
	buffer = (int16_t*) recvbuf;
	debug_info("%s",recvbuf);
	if(buffer[0] == dns_info->randid)
	{

	}
	else
		debug_info("recv error");
	return ret ;
}




