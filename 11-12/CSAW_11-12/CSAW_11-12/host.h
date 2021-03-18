#pragma once
#include <winsock.h>
#pragma warning(disable:4996)
class host
{
private:
	hostent* dns;
	char* addrs;
public:
	host(char* dns_addrs)
	{
		dns = gethostbyname(dns_addrs);
	}
	char* to_str()
	{
		IN_ADDR addr;
		memcpy(&addr.S_un.S_addr, dns->h_addr, dns->h_length);
		return inet_ntoa(addr);
	}
	~host()
	{

	}
};