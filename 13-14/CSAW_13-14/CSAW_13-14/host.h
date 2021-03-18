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
		return reinterpret_cast<char*>(dns->h_addr_list[0]);
	}
	~host()
	{

	}
};