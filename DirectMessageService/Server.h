#pragma once
#include "ListenerConnection.h"
#include "PollGroup.h"
#include "PacketImpl.h"
#include <unordered_set>
#include <functional>


// need an entered-text parser to convert raw char buf to proper Out PacketType
	// determine PacketType
	// make corresponding outPacket

class Server
{
public:
	Server(const char* host, const char* port);
	~Server();

	//int handleEvents();

private:
	ListenerConnection listener;
	std::unique_ptr<PollGroup> pollGroup;
	//std::unordered_map<SOCKET, std::string> users;

	//int acceptNewConnection();

};


class UserSet
{
public:

	//SOCKET getFdByName(const std::string& nm);
	//std::string& getNameByFd(SOCKET fd);

private:
	struct User
	{
		SOCKET fd;
		std::string username;

		bool operator==(const User& rhs);
		bool operator==(const std::string& nm);
		bool operator==(SOCKET fd);
	};

	std::unordered_set<User> mSet;
};


class RawTextParser
{
	// determinePacketType(std::stringview text)
		// if (inChannel && !firstNonWSIsEscapeChar(text))
			// packetType = MESSAGE
		// else if (firstNonWSIsEscapeChar(text))
			// packetType = interpretEscapeCharCmd(text)

	// std::pair<ServCommand, std::stringview> determineServCommand(std::stringview text)
	// {
		// std::pair<ServCommand, std::stringview> servCmdPair
		// auto [sc, sv] = servCmdPair
		// auto [cmdTxt, targTxt] = separateCmdAndTargetText(text)
		// if (cmdTxt == "talk")
		// {
			// if (alreadyInChannelWith(targTxt))
				// return
				
			// return { OPEN_CHANNEL, target }
		// }
		
		// if (command == "close")
		// {
			// if (!alreadyInChannelWith(target))
				// return DO_NOTHING

			// return { CLOSE_CHANNEL, target }
		// }
		// if (command == "help")
			// return { HELP, nullptr }

		// if (command == "list"

};				
				
				 