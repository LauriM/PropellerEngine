// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_NETWORK_CLIENTSYSTEM_H
#define ENGINE_NETWORK_CLIENTSYSTEM_H

#include "engine/SystemBase.h"
#include "engine/sys/Socket.h"
#include "engine/scene/Scene.h"
#include "engine/network/SharedEnums.h"

PROPELLER_FORWARD_DECLARE_2(engine, scene, Scene);
PROPELLER_FORWARD_DECLARE_2(engine, lang, HandleManager);

namespace engine {
namespace network {

	class ClientSystem : public SystemBase
	{
	public:
		ClientSystem(scene::Scene *scene, lang::HandleManager *handleManager);

		bool init();
		void uninit();
		void update(float delta);

		void connect();

		const String getName() { return "ServerSystem"; }

		// HACK: Client is "paused", this enables updating of the networking while not running the code locally
		const bool isGameplaySystem() { return false; }
	private:
		void handleNetworkCommand(ClientCommands cmd);

	private:
		bool connected;

		sys::Connection *clientConnection;

		scene::Scene *scene;
		lang::HandleManager *handleManager;
	};

}
}

#endif