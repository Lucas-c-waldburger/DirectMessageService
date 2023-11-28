#include "CreateSerialPacket.h"


//SerializedPacket::SerializedPacket() : SerialPacket()
//{}
//
//SerializedPacket::~SerializedPacket()
//{}
//
//void SerializedPacket::fill(std::unique_ptr<Packet> const& inData)
//{
//	if (!serialStr.empty())
//		throw std::runtime_error("SerializedPacket was not empty before serializing");
//
//	Packet::serialize(serialStr, inData);
//}
//
//const char* SerializedPacket::getCstr()
//{
//	return serialStr.c_str();
//}
//
//
//
//SerialPacketPool::SerialPacketPool(int startingAmount) : spPool(startingAmount)
//{}
//
//SerialPacketPool::SPptr SerialPacketPool::get()
//{
//	std::lock_guard<std::mutex> lg{mtx};
//
//	auto availableSp = findAvailable(true);
//	if (availableSp == spPool.end())
//	{
//		spPool.push_back(nullptr);
//		return SPptr{};
//	}
//
//	return std::move(*availableSp);
//}
//
//void SerialPacketPool::ret(SPptr& sp)
//{
//	std::lock_guard<std::mutex> lg{mtx};
//
//	auto empty = findAvailable(false);
//	if (empty == spPool.end())
//		throw std::runtime_error("This SerializedPacket was not properly registered with the pool");
//
//	sp->clear();
//
//	*empty = std::move(sp);
//}
//
//int SerialPacketPool::numAvailable()
//{
//	std::lock_guard<std::mutex> lg{mtx};
//
//	return std::count_if(spPool.begin(), spPool.end(), [](const SPptr& sp)
//		{
//			return sp != nullptr;
//		});
//}
//
//// false will flip to search for unavailable 
//std::vector<SerialPacketPool::SPptr>::iterator SerialPacketPool::findAvailable(bool yes)
//{
//	return std::find_if(spPool.begin(), spPool.end(), [&yes](const SPptr& sp)
//		{
//			return (sp == nullptr) == !yes;
//		});
//}
//
//DeSerializedPacket::DeSerializedPacket() : SerialPacket()
//{}
//
//DeSerializedPacket::~DeSerializedPacket()
//{}
//
