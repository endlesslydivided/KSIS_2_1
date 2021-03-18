#pragma once
#ifndef custom_arp_h__
#define custom_arp_h__

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <conio.h>
#include <Ws2tcpip.h>

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHlpApi.lib")

#include <iostream>

class custom_arp
{
	WSADATA wsaData;
public:
	void GetMacAddress(unsigned char* mac, struct
		in_addr destip)
	{
		DWORD ret;
		IPAddr srcip;
		ULONG MacAddr[2];
		ULONG PhyAddrLen = 6;
		int i;
		srcip = 0;
		//Послать ARP пакет
		ret = SendARP((IPAddr)destip.S_un.S_addr,
			srcip, MacAddr, &PhyAddrLen);
		//Преобразовать адрес
		if (PhyAddrLen)
		{
			BYTE* bMacAddr = (BYTE*)&MacAddr;
			for (i = 0; i < (int)PhyAddrLen; i++)
			{
				mac[i] = (char)bMacAddr[i];
			}
		}
	}
	int EntryPoint(const char* ip_address) noexcept
	{
		using std::cout;
		using std::cin;
		unsigned char mac[6];
		struct in_addr srcip = { 0 };
		struct sockaddr_in sa;
		/*WSADATA firstsock;
		if (WSAStartup(MAKEWORD(2, 2), &firstsock) != 0)
		{
			cout << "Ошибка инициализации winsock";
			cout << WSAGetLastError();
			return -1;
		}*/
		//преобразование IP адреса другим способом
		//srcip.s_addr = inet_addr(ip_address);
		inet_pton(AF_INET, ip_address, &(sa.sin_addr));
		//Получение MAC по IP
		GetMacAddress(mac, sa.sin_addr);
		//GetMacAddress(mac, srcip);
		printf("MAC адрес : %.2X-%.2X-%.2X-%.2X-%.2X-% .2X",
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		printf("\n");
		return 1;
	}
};
#endif // custom_arp_h__