#include "IPv4.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	if (argc <= 2)
	{
		cerr << "Неверное количество аргументов\n";
	}
	try
	{
		auto ip1 = ipv4<unsigned>(argv[1], argv[2]);
		cout << ip1 << endl;
	}
	catch (IPV4_Exception exception)
	{
		cerr << exception.get_message();
	}
	return 0;
}

