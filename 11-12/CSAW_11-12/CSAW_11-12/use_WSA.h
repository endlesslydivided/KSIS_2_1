#pragma once
#include "custom_arp.h"
class use_WSA {
	WSADATA d;
	WORD ver;
public:
	use_WSA() : ver(MAKEWORD(1, 1)) {
		if ((WSAStartup(ver, &d) != 0) || (ver != d.wVersion))
			throw(std::runtime_error("Error starting Winsock"));
	}
	~use_WSA() { WSACleanup(); }
};
