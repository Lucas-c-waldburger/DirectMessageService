#pragma once
#include "WSAInit.h"



namespace Utils
{
    void reportWSAErr(const std::string& location, int errCode);

    enum class Endian
    {
        TO_NETWORK,
        TO_HOST
    };

    template <typename T>
    void prepDataForSend(T data, char* buf);

    template <typename T>
    T convertDataByteOrder(T data, Endian byteOrdering);

    //void prepDataHtons(uint16_t shData, char* buf);
    //void prepDataHtonl(uint32_t lData, char* buf);
    //void prepDataNtohs(uint16_t shData, char* buf);
    //void prepDataNtohl(uint32_t lData, char* buf);

    void* castInAddrIPv(sockaddr* sa);

    addrinfo makeHints();

    int setSockReuse(SOCKET sockFd);

};

template<typename T>
inline void Utils::prepDataForSend(T data, char* buf)
{
    if (sizeof(buf) < sizeof(T))
        throw std::invalid_argument("buffer size too small to hold data type");

    T orderedData;

    switch (sizeof(T))
    {
    case (sizeof(uint8_t)):
        orderedData = data; break;
    case (sizeof(uint16_t)):
        orderedData = htons(data); break;
    case (sizeof(uint32_t)):
        orderedData = htonl(data); break;
    default:
        throw std::invalid_argument("invalid data size for hton operation");
    }

    memcpy(buf, &orderedData, sizeof(orderedData));
}

template<typename T>
inline T Utils::convertDataByteOrder(T data, Endian byteOrdering)
{
    T orderedData;

    switch (sizeof(T) + static_cast<size_t>(byteOrdering))
    {
    case (2):
        orderedData = htons(data); break;
    case (3):
        orderedData = ntohs(data); break;
    case (4):
        orderedData = htonl(data); break;
    case (5):
        orderedData = ntohl(data); break;
    default:
        throw std::invalid_argument("invalid data size for networking endian operation");
    }

    return orderedData;
}