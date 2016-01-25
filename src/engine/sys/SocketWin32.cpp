// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/Socket.h"
#include "engine/sys/Mutex.h"
#include "engine/memory/RingBuffer.h"

#if defined(OS_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning( push )
#pragma warning( disable: 4005 )

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma warning( pop )

namespace engine {
namespace sys {

	struct Connection
	{
		SOCKET socket;
		sockaddr_in dest;

		// Clientside related stuff, queue and mutex for accessing
		sys::Mutex *mutex;
		memory::RingBuffer *buffer;
	};

	struct SocketState
	{
		WSADATA wsaData;
	};

	SocketState state;

	void initNetworking()
	{
		int r = WSAStartup(MAKEWORD(2, 2), &state.wsaData);
		if (r != 0)
		{
			LOG_ERROR("[Socket] Cannot init networking!");
		}

		LOG_INFO("[Socket] Network init done!");
	}

	void uninitNetworking()
	{
		WSACleanup();
	}

	void networkReceiveThreadEntry(void *userData)
	{
		Connection *conn = (Connection*)userData;

		// Wait for data and query it up to the buffer
		for (;;)
		{
			sys::waitAndTakeMutex(conn->mutex);

			char buffer[150];

			int bytesReceived = recv(conn->socket, (char*)buffer[0], 150, 0);

			if (bytesReceived <= 0)
				continue;

			conn->buffer->insertData(buffer, bytesReceived);

			LOG_INFO("[NetworkThread] Recv: " << bytesReceived);

			sys::releaseMutex(conn->mutex);
		}
	}

	//TODO: move the mallocs to last on the functions, making sure they are only allocated if needed
	Connection *connectToServer()
	{
		Connection *conn = (Connection*)malloc(sizeof(Connection));

		conn->dest.sin_family = AF_INET;
		inet_pton(AF_INET, "127.0.0.1", &conn->dest.sin_addr.s_addr);
		conn->dest.sin_port = htons(8888);

		conn->socket = INVALID_SOCKET;

		if ((conn->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
		{
			LOG_WARNING("[Socket] failed with error code : " << WSAGetLastError());
			free(conn);
			return NULL;
		}

		if (connect(conn->socket, (sockaddr*)&conn->dest, sizeof(conn->dest)) == SOCKET_ERROR)
		{
			LOG_ERROR("[Socket] Failed to connect!");
			free(conn);
			return NULL;
		}

		LOG_INFO("[Socket] connection up!");

		conn->mutex = sys::createMutex();

		propellerCreateThread("NetworkReceiveThread", &networkReceiveThreadEntry, conn);

		//TODO HACK: this is not released!
		conn->buffer = new memory::RingBuffer(1024);

		return conn;
	}

	Connection *createServer(int port)
	{
		Connection *conn = (Connection*)malloc(sizeof(Connection));

		conn->buffer = NULL;

		conn->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (conn->socket == INVALID_SOCKET)
		{
			free(conn);
			return NULL;
		}

		struct sockaddr_in server;

		ZeroMemory(&server, sizeof(server));

		server.sin_family = AF_INET;
		server.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)127;
		server.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)0;
		server.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)0;
		server.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)1;
		server.sin_port = htons(port);

		if (bind(conn->socket, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
		{
			LOG_ERROR("Could not bind the socket. !!");
			free(conn);
			return NULL;
		}

		if(listen(conn->socket, SOMAXCONN) == SOCKET_ERROR)
		{
			LOG_ERROR("Cant listen to a socket!");
			free(conn);
			return NULL;
		}

		LOG_INFO("TCP server up on port " << port);

		// HACK HACK HACK WAIT ACCEPT THING
		
		return conn;
	}

	Connection *acceptClient(Connection *server)
	{
		SOCKET client = accept(server->socket, NULL, NULL);

		if (client == INVALID_SOCKET)
			return NULL;

		Connection *conn = new Connection();

		conn->socket = client;

		return conn;
	}

	// QQQ
	bool parsingHack = false;;

	void receiveData(Connection *conn, char *data, size_t maxLen, unsigned &bytesReceived)
	{
		// Server side doesn't have threads
		if (conn->buffer == NULL)
		{
			bytesReceived = recv(conn->socket, data, maxLen, 0);
			return;
		}

		bytesReceived = 0;

		sys::waitAndTakeMutex(conn->mutex);

		conn->buffer->getData(data, maxLen, bytesReceived);

		sys::releaseMutex(conn->mutex);
	}

	void sendData(Connection *conn, const char *data, size_t len)
	{
		sys::waitAndTakeMutex(conn->mutex);

		int result = send(conn->socket, data, len, 0);

		if (result == SOCKET_ERROR)
			LOG_ERROR("Socket broken!");

		sys::releaseMutex(conn->mutex);
	}

}
}

#endif

