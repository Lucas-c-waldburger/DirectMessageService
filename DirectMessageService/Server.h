#pragma once
#include "ListenerConnection.h"
#include "PollGroup.h"
#include "PacketImpl.h"
#include "UserSet.h"
#include <set>
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
	UserSet users;

	//int acceptNewConnection();

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
				
				 