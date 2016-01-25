// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/network/ClientSystem.h"
#include "engine/network/SharedEnums.h"
#include "engine/stream/InputStream.h"
#include "engine/component/ComponentHolder.h"
#include "engine/lang/HandleManager.h"

namespace engine {
namespace network {

	ClientSystem::ClientSystem(scene::Scene *scene, lang::HandleManager *handleManager)
		: connected(false)
		, scene(scene)
		, handleManager(handleManager)
	{ }

	bool ClientSystem::init()
	{
		PROFILE;

		return true;
	}

	void ClientSystem::connect()
	{
		//TODO: Move this to a separated call
		clientConnection = sys::connectToServer();

		if (clientConnection == false)
		{
			LOG_WARNING("Failed to connect to a server!");
			return;
		}

		// Send conn and handle that stuff

		ClientCommands cmd = CMD_CONN;

		sys::sendData(clientConnection, (char*)&cmd, sizeof(ClientCommands));

		LOG_INFO("Connected to a server!");

		connected = true;
	}

	void ClientSystem::uninit() { }

	void ClientSystem::update(float delta)
	{
		PROFILE;

		if (connected == false)
			return;

		unsigned bytesReceived;

		ClientCommands cmd = CMD_INVALID;

		unsigned packets = 0;
		unsigned bytes = 0;

		while (cmd != CMD_FRAMEDONE)
		{
			sys::receiveData(clientConnection, (char*)&cmd, sizeof(ClientCommands), bytesReceived);

			if (bytesReceived > 0)
			{
				handleNetworkCommand(cmd);
				packets++;
				bytes += bytesReceived;
			}
		}

		LOG_INFO(packets << "/" << bytes << "bytes");
	}

	void ClientSystem::handleNetworkCommand(ClientCommands cmd)
	{
		PROFILE;

		unsigned bytesReceived;

		//TODO: Change the strings to ClientCommand enum stuff

		if (cmd == CMD_CLRDATA)
		{
			// All data should be removed from the scene
			scene->resetScene();
			return;
		}

		if (cmd == CMD_SNAPSHOT)
		{
			// Server is sending full snapshot of the scene
			LOG_INFO("[ClientSystem] RECEIVING SNAPSHOT!");

			// Following data is going to be next:
			// unsigned int, size of the snapshot
			// _snapshot data_
			// _snapshot crc_ (MISSING !!!)
			size_t snapshotSize;
			sys::receiveData(clientConnection, (char*)&snapshotSize, sizeof(size_t), bytesReceived);

			LOG_INFO("Snapshot size: " << snapshotSize);

			// TODO: SOMETHING SANE HERE PERKELE
			char *buf = (char*)malloc(snapshotSize);

			sys::receiveData(clientConnection, buf, snapshotSize, bytesReceived);

			if (bytesReceived == snapshotSize)
			{
				LOG_INFO("Snapshot received ok!");

				stream::InputStream<stream::SerializationEndian> inputStream(buf);

				scene->load(inputStream);
			}
			return;
		}

		if (cmd == CMD_UPDATE_VEC3)
		{
			// We are about to receive 30 bits of vec3 data!
			unsigned len;
			char b[30];

			sys::receiveData(clientConnection, b, 30, len);

			if (len != 30)
			{
				LOG_WARNING("Connection out of sync!");
				return;
			}

			stream::InputStream<stream::SerializationEndian> inputStream(b);

			unsigned handle;
			unsigned propertyid;
			math::Vec3 pos;

			inputStream.read(handle);
			inputStream.read(propertyid);
			pos.load(inputStream);

			//LOG_INFO("Got pos for" << handle << " x: " << pos.x << " y: " << pos.y);

			stream::Serializable *ser = handleManager->getHandle(handle);

			if (ser == NULL)
			{
				LOG_WARNING("Out of sync!");
				return;
			}

			component::Component *comp = rtti::dynamicCast<component::Component>(ser);

			if (comp == NULL)
			{
				LOG_WARNING("Components out of sync!");
				return;
			}

			properties::PropertyVector properties = comp->getProperties();
			properties[propertyid].set(comp, pos);
		}
	}

}
}