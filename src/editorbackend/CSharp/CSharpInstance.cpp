// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/CSharp/CSharpInstance.h"

#include "../windows/EditorFrontend/Source Files/CppCommunication/StreamInstructionTypes.cs.h"

namespace editor {

	void CSharpInstance::writeInstructionCall()
	{
		callBufferStream.write((uint32_t)StreamInstructionTypes::STREAM_INSTRUCTION_CALL); //TODO: evil cast
	}

	void CSharpInstance::getCallBuffer(char **buf)
	{
		//Write EOF into the stream first
		callBufferStream.write((uint32_t)StreamInstructionTypes::STREAM_INSTRUCTION_EOF);

		//Give the ptr to the stream start
		*buf = (char*)callBufferStream.getData();
	}

	void CSharpInstance::finalizeSync()
	{
		callBufferStream.seekToStart();
	}

}