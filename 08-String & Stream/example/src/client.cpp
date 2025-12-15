#include "TCPStream.h"
#include <iostream>
#include <print>
#include <string_view>

int main()
{
    Network::Startup();
    Network::Socket connectSocket{ "127.0.0.1", 34567,
                                   Network::Socket::Tag::Connect };
    if (!connectSocket)
    {
        std::println("Connect socket error: {}", Network::GetErrorCode());
        return 1;
    }

    Network::OTCPStream stream;
    // buffer size设置为4字节，每4字节发送一次
    stream.open(std::move(connectSocket), 4);
    std::string str;
    for (int i = 0; i < 10; i++)
    {
        std::cin >> str;
        //每次输入后立刻发送
        stream << str << std::flush;
    }

    return 0;
}