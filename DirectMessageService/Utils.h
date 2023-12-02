#pragma once
#include "WSAInit.h"
#include <array>



namespace 
{
    namespace CExprJoinViews
    {
        template <const std::string_view&...strArgs>
        struct JoinViews
        {
            static constexpr auto joinImpl() noexcept
            {
                constexpr size_t len = (strArgs.size() + ... + 0);
                std::array<char, len + 1> arr{};

                int i = 0;
                auto append = [&i, &arr](auto const& sv) mutable
                {
                    for (auto ch : sv)
                        arr[i++] = ch;
                };

                (append(strArgs), ...);
                arr[len] = 0;

                return arr;
            }

            static constexpr auto joined = joinImpl();
            static constexpr std::string_view value {joined.data(), joined.size() - 1};
        };
    }

    template <const std::string_view&... strArgs>
    static constexpr auto joinViews = CExprJoinViews::JoinViews<strArgs...>::value;

    namespace CExprNumToStr
    {
        template<uint8_t... digits>
        struct PosToChars
        {
            static constexpr const char value[] = { ('0' + digits)..., 0 };
        };

        template<uint8_t... digits>
        struct NegToChars
        {
            static constexpr const char value[] = { '-', ('0' + digits)..., 0 };
        };


        template<bool neg, uint8_t... digits>
        struct ToChars : PosToChars<digits...>
        {};

        template<uint8_t... digits>
        struct ToChars<true, digits...> : NegToChars<digits...>
        {};


        template<bool neg, uintmax_t rem, uint8_t... digits>
        struct ProcessDecimals : ProcessDecimals<neg, rem / 10, rem % 10, digits...>
        {};

        template<bool neg, uint8_t... digits>
        struct ProcessDecimals<neg, 0, digits...> : ToChars<neg, digits...>
        {};


        template<typename T>
        constexpr uintmax_t cExprCabs(T num)
        {
            return (num < 0) ? -num : num;
        }
    };

    // enter just the typename "signed" or "unsigned" when calling
    template<typename Integer, Integer num>
    struct NumToStr : CExprNumToStr::ProcessDecimals<(num < 0), CExprNumToStr::cExprCabs(num)> // the "bool neg" template param in Process Decimals is evaluated in the parent struct template arg
    {};
};




// MOVE ALL THIS STUFF OUT
namespace Utils
{
    void reportWSAErr(const std::string& location, int errCode);

    constexpr size_t cExprStrlen(const char* s);


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