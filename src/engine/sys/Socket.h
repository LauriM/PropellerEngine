// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

// ################
// NOTE: The Socket implementation is a major hack, just to get trough the one course.
//       it should not be used in production at all !
// ################

#if defined(OS_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning( push )
#pragma warning( disable: 4005 )

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma warning( pop )

#endif

namespace engine {
namespace sys {

	// The server socket + bind
	struct Connection;

	struct IpAddress
	{
		unsigned long address;
		unsigned short port;
	};

	void initNetworking();
	void uninitNetworking();

	//TODO: Add the damn server ip & port to this!
	Connection *connectToServer();
	Connection *createServer(int port);

	// Receive one message, if possible
	void receiveData(Connection *conn, char *data, size_t maxLen, unsigned &bytesReceived);

	// Send data, if clientConnection is null, use conn->dest
	void sendData(Connection *conn, const char *data, size_t len);

	// Accept a connecting client
	Connection *acceptClient(Connection *server);

}
}
