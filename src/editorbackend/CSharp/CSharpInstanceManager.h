// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITORBACKEND_CSHARPINSTANCEMANAGER_H
#define EDITORBACKEND_CSHARPINSTANCEMANAGER_H

#include "editorbackend/CSharp/CSharpInstance.h"

#include "editorbackend/CSharp/CSharpInstanceType.h"

#include <vector>

namespace editor {

	class CSharpInstanceManager
	{
	private:
		typedef boost::unordered_map<String, CSharpInstanceType*> InstanceTypeMap;

	public:
		inline static InstanceTypeMap& getInstanceTypeMap(){
			static InstanceTypeMap staticInstanceTypeMap;
			return staticInstanceTypeMap;
		}

		static CSharpInstance* create(String name);
		static void release(CSharpInstance *instance);
		static void syncCSharpInstance(CSharpInstance *instance, const char *in, char **out);
		static void finalizeSync(CSharpInstance *instance);

		static void registerInstanceType(String name, CSharpInstanceType *type);

	private:
		static void processInputStream(CSharpInstance *instance, const char *buffer);
		static void processOutputStream(CSharpInstance * instance, char **out);
	};

}

#endif