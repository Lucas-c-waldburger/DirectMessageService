#pragma once
#include "Utils.h"
#include <vector>

// Need add:
	// listener
	// way to safely iterate through
	// way to remove disconnects while iterating

// must init with valid listener socket, listener must exist for entire time pollgroup exists
class PollGroup
{
public:
	using IterPair = std::pair<std::vector<pollfd>::iterator, std::vector<pollfd>::iterator>;

	PollGroup(SOCKET listener);
	PollGroup(SOCKET listener, int timeO);
	~PollGroup() = default;

	void add(SOCKET sockFd, short events);
	bool remove(SOCKET sockFd);
	int poll();
	int size();

	const SOCKET& listenerFd();
	IterPair getIters();

private:
	std::vector<pollfd> pfds;
	int timeout;
};

