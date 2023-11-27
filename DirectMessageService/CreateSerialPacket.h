#pragma once
#include "Packet.h"
#include <mutex>


class SerializedPacket
{
public:
	void fill(std::unique_ptr<Packet> const& pack);
	void clear();
	const char* getCstr();

private:
	std::string serialStr;

};

// thread-safe Object Pool to handle clearing and moving serialPackets to different server serialization processes 
class SerialPacketPool
{
public:
	using SPptr = std::unique_ptr<SerializedPacket>;

	SerialPacketPool(int startingAmount);

	SPptr get();
	void ret(SPptr& sp);

	int numAvailable();

private:
	std::mutex mtx;
	std::vector<SPptr> spPool;

	std::vector<SPptr>::iterator findAvailable(bool yes);
};
   


class CreatePacket
{








};