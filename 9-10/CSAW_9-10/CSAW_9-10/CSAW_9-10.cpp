#include "custom_arp.h"

#include <Windows.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <algorithm>
#include <iterator>
#include <iostream> 
using namespace std;
string RemoveSpaces(string& str)
{
	str.erase
	(
		unique_copy(str.begin(), str.end(), str.begin(),[](char c1, char c2) { return c1 == ' ' && c2 == ' '; }),
		str.end()
	);
	str.erase(str.begin());
	return str;
}
string execute(const char* cmd)
{
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&_pclose) > pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	int string_iter = 0;
	for (auto i = result.end(); i > result.begin(), string_iter != 15; i--, string_iter++)
		result.erase(i);
	return RemoveSpaces(result);
}
int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	if (argc > 3 || argc == 1)
	{
		cout << "Неверный ввод\n";
		return 0;
	}
	custom_arp arp;
	try
	{
		if (!strcmp(argv[1], "/ip"))
			arp.EntryPoint(argv[2]);
		if (!strcmp(argv[1], "/mac"))
		{
			string res = "arp -a | find /i ";
			res += "\"";
			res += argv[2];
			res += "\"";
			cout << execute(res.c_str());
		}
	}
	catch (exception e)
	{
		cout << e.what();
	}

	return 0;
}