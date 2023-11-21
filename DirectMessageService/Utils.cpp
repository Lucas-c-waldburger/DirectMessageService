#include "Utils.h"



void Utils::reportWSAErr(const std::string& location, int errCode)
{
    const auto errCond = std::system_category().default_error_condition(errCode);

    std::cout << "ERROR: " << location << '\n'
              << "Category: " << errCond.category().name() << '\n'
              << "Value: " << errCond.value() << '\n'
              << "Message: " << errCond.message() << '\n';
}

//void Utils::prepDataHtons(uint16_t shData, char* buf)
//{
//    if (sizeof(buf) < sizeof(uint16_t))
//        throw std::invalid_argument("buffer size not large enough to hold 16 bytes");
//
//    uint16_t nbo = htons(shData);
//    memcpy(buf, &nbo, sizeof(nbo));
//}
//
//void Utils::prepDataHtonl(uint32_t lData, char* buf)
//{
//    if (sizeof(buf) < sizeof(uint32_t))
//        throw std::invalid_argument("buffer size not large enough to hold 16 bytes");
//
//    uint32_t nbo = htonl(lData);
//    memcpy(buf, &nbo, sizeof(nbo));
//}
//
//void Utils::prepDataNtohs(uint16_t shData, char* buf)
//{
//    if (sizeof(buf) < sizeof(uint16_t))
//        throw std::invalid_argument("buffer size not large enough to hold 16 bytes");
//
//    uint16_t nbo = htons(shData);
//    memcpy(buf, &nbo, sizeof(nbo));
//
//}

//void Utils::readBackDataNtohs(char* buf, uint16_t& shData)
//{
//    memcpy(&shData, buf, sizeof(shData));
//}

void* Utils::castInAddrIPv(sockaddr* sa)
{
    if (sa->sa_family == AF_INET)
        return &(((sockaddr_in*)sa)->sin_addr);

    return &(((sockaddr_in6*)sa)->sin6_addr);
}

addrinfo Utils::makeHints()
{
    addrinfo hints{};
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    return hints;
}

int Utils::setReuse(SOCKET sockFd)
{
    int yes = 1;
    return setsockopt(sockFd, SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR, (const char*)&yes, sizeof(yes));
}

