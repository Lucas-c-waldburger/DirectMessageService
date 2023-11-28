#pragma once
#include "Packet.h"
#include <mutex>

// TODO: Decide if we need all this!!!



//template <typename T, typename U>
//class SerialPacket
//{
//public:
//	SerialPacket();
//	virtual ~SerialPacket();
//
//	virtual T fill(U inData) = 0;
//	void clear();
//
//protected:
//	std::string serialStr;
//};
//
//
//class SerializedPacket : public SerialPacket<void, std::unique_ptr<Packet> const&>
//{
//public:
//	SerializedPacket();
//	virtual ~SerializedPacket();
//
//	void fill(std::unique_ptr<Packet> const& inData) override;
//	const char* getCstr();
//};
//
//class DeSerializedPacket : public SerialPacket<std::unique_ptr<Packet>, const char*>
//{
//public:
//	DeSerializedPacket();
//	virtual ~DeSerializedPacket();
//
//	std::unique_ptr<Packet> fill(const char* inData) override;
//	const std::string& getSerialStr();
//};
//
//// thread-safe Object Pool to handle clearing and moving serialPackets to different server serialization processes 
//class SerialPacketPool
//{
//public:
//	using SPptr = std::unique_ptr<SerializedPacket>;
//
//	SerialPacketPool(int startingAmount);
//
//	SPptr get();
//	void ret(SPptr& sp);
//
//	int numAvailable();
//
//private:
//	std::mutex mtx;
//	std::vector<SPptr> spPool;
//
//	std::vector<SPptr>::iterator findAvailable(bool yes);
//};
//   
//
//template<typename T, typename U>
//inline SerialPacket<T, U>::SerialPacket()
//{}
//
//template<typename T, typename U>
//inline SerialPacket<T, U>::~SerialPacket()
//{}
//
//template<typename T, typename U>
//inline void SerialPacket<T, U>::clear()
//{
//	serialStr.clear();
//}
