// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_NETWORK_SERVERSYSTEM_H
#define ENGINE_NETWORK_SERVERSYSTEM_H

#include "engine/SystemBase.h"
#include "engine/sys/Socket.h"
#include "engine/scene/Scene.h"
#include "engine/network/SharedEnums.h"
#include "engine/sys/Timer.h"

#define MAX_CLIENTS 32

namespace engine {
namespace network {

	// Handles the server side stuff of networking, binds the ports,
	// handles what date should be synced where, etc.
	// Only present on server side.
	class ServerSystem : public SystemBase
	{
	private:
		scene::Scene *scene;
		sys::Timer tickTimer;

	public:
		ServerSystem(scene::Scene *scene)
			: scene(scene)
		{ }

		bool init();
		void uninit();
		void update(float delta);

		const String getName() { return "ServerSystem"; }

	private:
		void handleIncomingData();
		void updateClients();

		void sendFullsnapshotToClient(sys::Connection *conn);

		void sendCMDToActiveClients(const ClientCommands cmd);
		void sendDataToActiveClients(const char *data, size_t len);

		sys::Connection *serverConnection;

		sys::Connection *clientHack;
	};

}
}

#endif
