#pragma once
#include "App.h";

class DMChannel
{
public:
	DMChannel(SOCKET recFd, const std::string& senderUsrnm);


private:
	SOCKET recipientFd;
	std::string senderUsername;

	class AssembledMessage
	{
	public:
		AssembledMessage(const std::string& senderUsrnm);

		bool empty();
		void set(const std::string& typedMsg);
		const std::string& get();

	private:
		std::string mMsg;
		int lenUsrnmDecoration;

		void clear();
	} assembledMsg;

};

