#pragma once
#include <type_traits>
#include <string>
#include <regex>
#include <cassert>
#include <exception>
#include <sstream>
#include <iostream>

using namespace std;

namespace CSAW_6
{

    typedef string address;

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

    class IPV4_Exception
    {
        string message;
    public:
        explicit IPV4_Exception(string message) : message(message) {}
        string get_message() noexcept { return  this->message; }
        ~IPV4_Exception() {}
    };

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

    template<typename T>
    constexpr  bool IsUnsigned = is_same<T, unsigned>::value;

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

    template<typename T>
    struct ADDRESS
    {
        static_assert(IsUnsigned<T>, "ipv4 должно быть типа unsigned");
        T first : 8; T second : 8; T third : 8;T fourth : 8;
        friend const ADDRESS& operator& (ADDRESS a1, ADDRESS a2) noexcept
        {
            ADDRESS a = { a1.first & a2.first, a1.second & a2.second,  a1.third & a2.third,  a1.fourth & a2.fourth };
            return a;
        }
        const ADDRESS& operator~ () noexcept
        {
            return
            { ~this->first,
              ~this->second,
              ~this->third,
              ~this->fourth };
        }
        friend const ADDRESS& operator| (ADDRESS a1, ADDRESS a2) noexcept
        {
            ADDRESS a = { a1.first | a2.first, a1.second | a2.second,  a1.third | a2.third,  a1.fourth | a2.fourth };
            return a;
        }
        string to_str() noexcept
        {
            string str;
            stringstream ss(str);
            ss << this->first << '.' << this->second << '.' << this->third << '.' << this->fourth;
            str = ss.str();
            return str;
        }
    };
    inline bool CheckIpAddress(const string& str_)
    {
        regex valid_ip("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$",regex_constants::ECMAScript);
        return regex_search(str_, valid_ip);

    }
    inline bool CheckISubnetMask(const string& str_)
    {
        regex valid_ip("^(((255\\.){3}(255|254|252|248|240|224|192|128|0+))| ((255\\.){2}(255|254|252|248|240|224|192|128|0+)\\.0)|((255\\.)(255|254|252|248|240|224|192|128|0+)(\\.0+){2})|((255|254|252|248|240|224|192|128|0+)(\\.0+){3}))$",regex_constants::ECMAScript);
        return regex_search(str_, valid_ip);

    }

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

    template<typename T>
    ADDRESS<unsigned> StringToAddress(string str)
    {
        ADDRESS<unsigned> address_out;
        stringstream tmp_ip(str);
        unsigned int octet1; unsigned int octet2; unsigned int octet3; unsigned int octet4;
        char dot;
        tmp_ip >> octet1 >> dot >> octet2 >> dot >> octet3 >> dot >> octet4;
        address_out = { octet1, octet2, octet3, octet4 };
        return address_out;
    }

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

    template<typename T>
    class ipv4
    {
        static_assert(IsUnsigned<T>, "ipv4 должен быть unsigned");
    private:

        address ip;
    public:
        address GetIP() const
        {
            return ip;
        }

        void SetIP(const address& ip)
        {
            ipv4::ip = ip;
        }

        address GetMask() const
        {
            return mask;
        }

        void SetMask(const address& mask)
        {
            ipv4::mask = mask;
        }

        address GetSubnet()
        {
            return StringToAddress<unsigned>(ip) & StringToAddress<unsigned>(mask);
        }

        address GetHost() const
        {
            return StringToAddress<unsigned>(ip) & ~StringToAddress<unsigned>(mask);
        }

    private:
        address mask;
        address subnet;
        address host;
        address broadcast;
    public:
        address GetBroadcast() const
        {
            return StringToAddress<unsigned>(subnet) | ~StringToAddress<unsigned>(mask);
        }

    public:
        ipv4(const address& ip, const address& mask);
        ~ipv4();

    public:
        friend ostream& operator<<(ostream& io, ipv4<T> ipv4_out) noexcept
        {
            return io << "IP: " << ipv4_out.ip << endl <<
                "Маска: " << ipv4_out.mask << endl <<
                "Подсеть: " << ipv4_out.subnet << endl <<
                "Хост: " << ipv4_out.host << endl <<
                "Широковещательная сеть: " << ipv4_out.broadcast;
        }
    };
}

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

using namespace CSAW_6;
template<typename T>
ipv4<T>::ipv4(const address& ip, const address& mask)
{

    if (!CheckIpAddress(ip))
    {
        throw IPV4_Exception("Неверные IP-адрес: " + ip);
    }
    if (!CheckISubnetMask(mask))
    {
        throw IPV4_Exception("Неверная маска подсети: " + mask);
    }
    this->ip = ip;
    this->mask = mask;
    ADDRESS<T> getip = StringToAddress<unsigned>(ip);
    ADDRESS<T> getmask = StringToAddress<unsigned>(mask);
    ADDRESS<T> getsub = getip & getmask;
    ADDRESS<T> gethost = getip & (~getmask);
    ADDRESS<T> getbroadcast = getsub | ~getmask;

    this->subnet = getsub.to_str();
    this->host = gethost.to_str();
    this->broadcast = getbroadcast.to_str();
}

//▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬

template<typename T>
ipv4<T>::~ipv4()
{

}


