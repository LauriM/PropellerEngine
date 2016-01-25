// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/Socket.h"

#if defined(OS_LINUX) || defined(OS_ANDROID)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace engine {
namespace sys {

	struct Connection
	{
		int socket;
	};

	void initNetworking()
	{
		LOG_WARNING("[Socket] Networking is a stub on Linux!");
	}

	void uninitNetworking() { }

	Connection *connectToServer() { return NULL; }

	Connection *createServer(int port)
	{
		struct sockaddr_in serverAddr;

		Connection *conn = (Connection*)malloc(sizeof(Connection));

		conn->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if(conn->socket == -1)
		{
			LOG_ERROR("Failed to create server!");
			free(conn);
			return NULL;
		}

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serverAddr.sin_port = htons(port);

		bind(conn->socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

		//TODO: check if bind ok

		return conn;
	}

	// Receive one message, if possible
	void receiveData(Connection *conn, char *data, size_t maxLen, unsigned &bytesReceived) { }

	// Send data, if clientConnection is null, use conn->dest
	void sendData(Connection *conn, const char *data, size_t len) { }

	// Accept a connecting client
	Connection *acceptClient(Connection *server) { }

}
}

#endif

