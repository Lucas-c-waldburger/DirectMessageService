#pragma once
#include "Packet.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>








class PacketSerializer
{
public:

    template <class T>
    static void serializeToString(std::string& serialStr, const TimePoint& tp)
    {
        serialStr.clear();

        boost::iostreams::back_insert_device<std::string> inserter(serialStr);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> stream(inserter);
        boost::archive::binary_oarchive oa(stream);

        oa << tp;

        stream.flush();


    };

    void deSerialize(const std::string& serialStr, TimePoint& tp)
    {
        boost::iostreams::basic_array_source<char> device(serialStr.data(), serialStr.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char>> stream(device);
        boost::archive::binary_iarchive ia(stream);

        ia >> tp;
    }


};

