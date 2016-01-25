// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

namespace engine {
namespace network {

	//TODO: RENAME TO NETWORK CMD
	enum ClientCommands
	{
		CMD_INVALID = -1,
		CMD_CONN = 30,
		CMD_UPDATE_VEC3,
		CMD_CLRDATA,
		CMD_SNAPSHOT,
		CMD_FRAMEDONE, // UBER HACK PERKELE
	};

}
}