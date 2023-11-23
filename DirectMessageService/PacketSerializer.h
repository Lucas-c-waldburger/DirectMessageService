#pragma once
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/access.hpp>



namespace PacketSerializer
{
    template <class T>
    inline void serializeToString(std::string& serialStr, const T& obj)
    {
        boost::iostreams::back_insert_device<std::string> inserter(serialStr);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> stream(inserter);
        boost::archive::binary_oarchive oa(stream);

        oa << obj;

        stream.flush();
    };

    template <class T>
    inline void deSerialize(const std::string& serialStr, T& obj)
    {
        boost::iostreams::basic_array_source<char> device(serialStr.data(), serialStr.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char>> stream(device);
        boost::archive::binary_iarchive ia(stream);

        ia >> obj;
    }


};

