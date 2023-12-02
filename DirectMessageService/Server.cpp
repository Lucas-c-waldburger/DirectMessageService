#include "Server.h"

Server::Server(const char* host, const char* port) : pollGroup(nullptr), validateUsername(users)
{
	if (!listener.setUp(host, port))
		throw std::runtime_error("Server set up failed");

	if (!listener.startListen())
		throw std::runtime_error("Server set up failed");

	pollGroup = std::make_unique<PollGroup>(*listener.getFd());

	std::cout << "Server set up successful. Listening for new connections...\n";
}

Server::~Server() 
{}

bool Server::eventLoop()
{
	int numEvents;
	SOCKET newFd;
	sockaddr_storage addrStore;
	socklen_t addrLen;
	char buf[256];
	char remoteIP[INET6_ADDRSTRLEN];
	const SOCKET& listenerFd = pollGroup->listenerFd();

	bool running = true;
	while (running)
	{
		numEvents = pollGroup->poll();

		if (numEvents == SOCKET_ERROR)
		{
			reportWSAErr("poll()", WSAGetLastError());
			return false;
		}

		if (!numEvents)
			continue;

		//// MAIN LOOP ////

		auto [it, end] = pollGroup->getIters();

		for (; it != end; it++)
		{
			if (!(it->revents & POLLIN))
				continue;

			if (it->fd == listenerFd)
			{
				addrLen = sizeof(addrStore);

				newFd = accept(listenerFd, (sockaddr*)&addrStore, &addrLen);
				
				if (newFd == SOCKET_ERROR)
				{
					reportWSAErr("accept()", WSAGetLastError());
					continue;
				}

				inet_ntop(addrStore.ss_family, (sockaddr*)&addrStore, remoteIP, INET6_ADDRSTRLEN);

				if (!remoteIP)
					reportWSAErr("inet_ntop()", WSAGetLastError());

				pollGroup->add(newFd, POLLIN);

				std::cout << "Poll Server: new connection from " << remoteIP << " on socket " << newFd << '\n'
						  << "Requesting username...";

				// TODO: Send a success message!!!
				//if (send(newFd, askUsernameBuf.data(), askUsernameBuf.maxLen(), 0) == SOCKET_ERROR)
					//reportWSAErr("send()", WSAGetLastError());
			}

			else // user 
			{
				const SOCKET& userFd = it->fd;

				// recv all data into recv buffer
				recvAll(userFd);

				// deserialize the packet sent by the user, return its type
				auto& packetType = recvHandler.toPacket();  

				switch (packetType)
				{
				case MESSAGE:
				{
					auto& msgPacket = recvHandler.getMsgPacket();

					switch (msgPacket.getMsgType())
					{
					case USERNAME_REQ: // client trying to register a username they sent over
					{
						// check if user has a registered username
						if (users.hasUsername(userFd))
						{
							// set SendHandler buffer to appropriate fail msg
							// break;
						}

						std::string_view usernameView{msgPacket.getMsgStr()}; // make a view of the username
						std::string_view retMsg = validateUsername(usernameView); 

						if (Validation::success(retMsg))
						{
							// set SendHandler buffer to success msg
							users.add(userFd, msgPacket.getMsgStr());
						}

						else
						{
							// set SendHandler buffer to retMsg
							
						}

						break;
					}
					// OTHER CASES
					case DIRECT_MSG:
					{
						if (!users.hasUsername(userFd))
						{
							// set SendHandler buffer to appropriate fail msg
							// break;
						}





					}
				}
				case SERVER_COMMAND:










				}
				}





				

			}






		}


	}
}

bool Server::recvAll(SOCKET fd)
{
	recvHandler.getRecvBuf().clear();

	size_t offset = 0;
	int numBytesRecv = 0;

	do
	{
		numBytesRecv = recv(fd, 
							recvHandler.getRecvBuf().data() + offset, 
							recvHandler.getRecvBuf().maxLen() - offset, 
							0);

		if (numBytesRecv <= 0)
		{
			if (numBytesRecv == SOCKET_ERROR)
				reportWSAErr("recv()", WSAGetLastError());

			else if (numBytesRecv == 0)
				std::cout << "Connection closed by client on socket " << fd << '\n';

			disconnectUser(fd);
			return false;
		}

		// else got data in buf
		offset += numBytesRecv;

		if (offset >= recvHandler.getRecvBuf().maxLen())
		{
			std::cout << "Error: RecvBuffer could not hold all data sent by client on socket " << fd << '\n';
			return false;
		}

	} while (recvHandler.getRecvBuf().data()[offset - 1] != 0);

	return true;
}



// will only return false if closesocket() fails. 
// Error conditions from pollGroup.remove() and
// users.remove() only suggest that the socket
// was connected, but never stored in those structures
bool Server::disconnectUser(SOCKET fd)
{
	if (closesocket(fd) == SOCKET_ERROR)
	{
		reportWSAErr("SC_getAddrInfo()", WSAGetLastError());
		return false;
	}

	std::cout << "Socket " << fd << " closed\n";

	if (!pollGroup->remove(fd))
		std::cout << "Error removing socket " << fd << "from Poll Group\n";

	if (!users.remove(fd))
		std::cout << "Error removing socket " << fd << "from User Set\n";

	return true;
}

