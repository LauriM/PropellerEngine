// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/network/ServerSystem.h"
#include "engine/sys/Socket.h"
#include "engine/scene/Scene.h"
#include "engine/stream/BufferedOutputStream.h"
#include "engine/network/SharedEnums.h"
#include "engine/sys/Sleep.h"
#include "engine/console/Cvar.h"

namespace cvar {
	CVAR(int, sv_tickrate, 30, false);
}

namespace engine {
namespace network {

	bool ServerSystem::init()
	{
		serverConnection = sys::createServer(8888);
		if(serverConnection == NULL)
		{
			LOG_ERROR("[ServerSystem] Failed to create a server!");
			return false;
		}

		LOG_INFO("[ServerSystem] Server started up on port 8888");

		LOG_INFO("   #####         ACCPETING SINGLE CLIENT BECAUSE PERKELE    #### ");

		clientHack = sys::acceptClient(serverConnection);
		LOG_INFO("   #####         DONE! ####");

		tickTimer.start();

		return true;
	}

	void ServerSystem::uninit() { }

	void ServerSystem::update(float delta)
	{
		PROFILE;

		handleIncomingData();

		//float t = (1.f / *cvar::sv_tickrate) / 100.f;

		// HACK: TICKRATE IS HACKED WITH THESE CALCULATIONS TO 20
		float t = 50.f;
		float t2 = float(tickTimer.getTimeInMilliSeconds());

		if (t2 > t)
		{
			// Updating clients is done with a tickrate
			updateClients();

			tickTimer.start();
		}
	}

	bool connHack = false;

	void ServerSystem::handleIncomingData()
	{
		PROFILE;
		//TODO: Move this to a separated thread handled by ServerSystem, handle the Queue here

		//TODO: LOOP TROUGH ALL THE DIFFERENT CONNECTIONS THAT THE SERVER HAS !!

		if (connHack == true)
			return;  // Connection done, lets NOT listen to client, threading not implemented

		unsigned bytesReceived;

		ClientCommands buffer;

		receiveData(clientHack, (char*)&buffer, sizeof(ClientCommands), bytesReceived);

		if (bytesReceived == 0)
			return; // nothing received, move on

		if (buffer == CMD_CONN)
		{
			connHack = true;
			// NEW CONNECTION!
			LOG_INFO("New client connected!");

			//  HACK HACK
			sendFullsnapshotToClient(clientHack);
		}

		// Okey, we should handle the commands we get from the client...
	}

	void ServerSystem::updateClients()
	{
		PROFILE;

		stream::BufferedOutputStream<stream::SerializationEndian> outputStream;

		// First check the clients for anyone needing a fullsnapshot

		// Go trough the scene to see partial updates

		//TODO: Add optimization to have the "property"/"component"/"entity" marked dirty
		const scene::Scene::EntityList *entityList = scene->getEntityList();

		for (unsigned i = 0; i < entityList->size(); ++i)
		{
			scene::Entity *ent = entityList->at(i);

			const component::ComponentHolder::ComponentList &components = ent->getComponents();

			for (unsigned x = 0; x < components.size(); ++x)
			{
				properties::PropertyVector &properties = components[x]->getProperties();

				for (unsigned y = 0; y < properties.size(); ++y)
				{
					if (properties[y].isDirty(components[x]))
					{
						if (properties[y].getType() == properties::PropertyTypeVec3)
						{
							math::Vec3 pos = properties[y].get_Vec3(components[x]);

							sendCMDToActiveClients(CMD_UPDATE_VEC3);

							outputStream.reset();

							// Sending over the following data:
							//
							// CMD_UDPATE_VEC3
							//
							// SIZE IS GOING TO BE 30
							//  -> component handle
							//  -> property id
							//  -> Vec3 serialized

							outputStream.write(components[x]->getHandleId());
							outputStream.write(y);
							pos.save(outputStream);

							sendDataToActiveClients((char*)outputStream.getData(), outputStream.getSize());
							//LOG_INFO("handle: " << components[x]->getHandleId() << "propid: " << y);
						}

						properties[y].clearDirty(components[x]);
					}
				}
			}
		}

		sendCMDToActiveClients(CMD_FRAMEDONE);
	}

	void ServerSystem::sendDataToActiveClients(const char *data, size_t len)
	{
		/*
		for (unsigned i = 0; i < MAX_CLIENTS; ++i)
			if (clients[i].connected == true)
			*/

		sys::sendData(clientHack, data, len);

	}

	void ServerSystem::sendCMDToActiveClients(const ClientCommands cmd)
	{
		sendDataToActiveClients((char*)&cmd, sizeof(ClientCommands));
	}

	void ServerSystem::sendFullsnapshotToClient(sys::Connection *conn)
	{
		PROFILE;

		const scene::Scene::EntityList *entityList = scene->getEntityList();

		// Clear all entities on client side
		ClientCommands cmd = CMD_CLRDATA;
		sendDataToActiveClients((char*)&cmd, sizeof(ClientCommands));

		cmd = CMD_SNAPSHOT;
		sendDataToActiveClients((char*)&cmd, sizeof(ClientCommands));

		stream::BufferedOutputStream<stream::SerializationEndian> dataStream;

		scene->save(dataStream);

		size_t size = dataStream.getSize();

		sys::sendData(clientHack, (char*)&size, sizeof(size_t));
		sys::sendData(clientHack, (char*)dataStream.getData(), dataStream.getSize());

		// TODO: set snapshot requirement flag to false
	}

}
}
