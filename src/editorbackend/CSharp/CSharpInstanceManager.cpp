// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "engine/stream/BufferedOutputStream.h"
#include "engine/stream/CSharpInputStream.h"
#include "../windows/EditorFrontend/Source Files/CppCommunication/StreamInstructionTypes.cs.h"
#include "engine/sys/Logger.h"
#include "engine/sys/Mutex.h"

namespace editor {

	engine::sys::Mutex *instanceProcessingMutex;

	CSharpInstance* CSharpInstanceManager::create(String name)
	{
		if (instanceProcessingMutex == NULL)
			instanceProcessingMutex = engine::sys::createMutex();

		InstanceTypeMap::iterator it = getInstanceTypeMap().find(name);

		if(it == getInstanceTypeMap().end())
		{
			LOG_ERROR("Can't find requested C# Instance type!");
			return NULL;
		}

		DEBUG_PRINT("Creating C# Instance of " << name);

		//Lets create the new instance...
		CSharpInstance *inst = it->second->create();

		inst->init();
		inst->setName(name);

		return inst;
	}

	void CSharpInstanceManager::release(CSharpInstance *instance)
	{
		instance->uninit();
		DEBUG_PRINT("Destroying C# Instance of " << instance->getName());
		delete instance;
	}

	void CSharpInstanceManager::registerInstanceType(String name, CSharpInstanceType *type)
	{
		getInstanceTypeMap().insert(InstanceTypeMap::value_type(name, type));
	}

	void CSharpInstanceManager::syncCSharpInstance(CSharpInstance *instance, const char *in, char **out)
	{
		engine::sys::waitAndTakeMutex(instanceProcessingMutex);

		processInputStream(instance, in);

		//Processing done, lets get the streams and build a message back!

		processOutputStream(instance, out);

		engine::sys::releaseMutex(instanceProcessingMutex);
	}

	void CSharpInstanceManager::processInputStream(CSharpInstance *instance, const char *buffer)
	{
		engine::stream::CSharpInputStream stream((void*)buffer);

		int streamInstruction;
		String name;

		for (;;)
		{
			stream.read(streamInstruction);

			switch (streamInstruction)
			{
			case StreamInstructionTypes::STREAM_INSTRUCTION_EOF:
				return;

			case StreamInstructionTypes::STREAM_INSTRUCTION_CALL:
				stream.read(name);
				
				instance->handleEvent(name, stream);
				break;
			default:
				DEBUG_PRINT("Stream instruction not detected!");
				return;
			}
		}
	}

	void CSharpInstanceManager::processOutputStream(CSharpInstance * instance, char **out)
	{
		instance->getCallBuffer(out);
	}

	void CSharpInstanceManager::finalizeSync(CSharpInstance *instance)
	{
		instance->finalizeSync();
	}

}