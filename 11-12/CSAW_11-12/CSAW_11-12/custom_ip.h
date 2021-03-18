#pragma once
#include <winsock.h>
#pragma warning(disable:4996)
class custom_ip
{
private:
	hostent* dns;
	char* addrs;
	in_addr addr;
public:
	custom_ip(char* ip_addrs)
	{
		addr.S_un.S_addr = inet_addr(ip_addrs); //преобразование
		dns = gethostbyaddr((char*)&addr, 4, AF_INET);
	}
	char* to_str()
	{
		return reinterpret_cast<char*>(dns->h_name);
	}
	~custom_ip()
	{

	}
};