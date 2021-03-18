#include "custom_arp.h"
#include "use_WSA.h"
#include <regex>
#pragma warning(disable:4996)
using namespace std;

bool CheckDNSName(const char* dns_name)
{
	std::regex valid_dns("^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$", std::regex_constants::ECMAScript);
	return std::regex_search(dns_name, valid_dns);
}

int main(int argc, char* argv[])
{
	if (argc < 2) 
	{
		std::cerr << "Usage: resolve <host-name>";
		return EXIT_FAILURE;
	}

	try 
	{
		setlocale(LC_ALL, "rus");
		use_WSA wsa;
		hostent* h = gethostbyname(argv[1]);
		in_addr addrs;
		unsigned char* addr = reinterpret_cast<unsigned char*>(h->h_addr_list[0]);
		addrs.s_addr = *(u_long*)h->h_addr_list[0];
		custom_arp arp;
		arp.entry_point(inet_ntoa(addrs));
	}
	catch (std::exception const& exc) {
		std::cerr << exc.what() << "\n";
		return EXIT_FAILURE;
	}
	
	return 0;
}
