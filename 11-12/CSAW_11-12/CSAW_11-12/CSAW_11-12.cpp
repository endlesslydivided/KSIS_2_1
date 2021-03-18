#include "use_WSA.h"
#include <regex>
#include "host.h"
#include "custom_ip.h"
#pragma warning(disable:4996)
using namespace std;

bool CheckDNSName(const char* dns_name)
{
	std::regex valid_dns("^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$", std::regex_constants::ECMAScript);
	return std::regex_search(dns_name, valid_dns);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	if (argc > 3 || argc == 1)
	{
		std::cout << "Неверное количество аргументов\n";
		return 0;
	}
	custom_arp arp;
	try
	{
		use_WSA socket_init;
		if (!std::strcmp(argv[1], "/ip"))
		{

			custom_ip h(argv[2]);
			std::cout << h.to_str();
		}
		if (!std::strcmp(argv[1], "/dns"))
		{
			host h(argv[2]);
			std::cout << h.to_str();
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}

	return 0;
}