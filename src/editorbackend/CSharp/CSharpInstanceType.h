// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITORBACKEND_CSHARPINSTANCETYPE_H
#define EDITORBACKEND_CSHARPINSTANCETYPE_H

#define REGISTER_CSHARPINSTANCE(p_name) GenerateCSharpInstanceType<p_name> __csharpInstanceType##p_name(TO_STRING(p_name));

namespace editor {

	class CSharpInstanceType
	{
	public:
		virtual CSharpInstance *create() = 0;
		virtual void release(CSharpInstance *inst) = 0;
	};

	template <typename T>
	class GenerateCSharpInstanceType : public CSharpInstanceType
	{
	public:
		GenerateCSharpInstanceType(String name)
		{
			DEBUG_PRINT("[REGISTERING C# Instance] " << name);
			CSharpInstanceManager::registerInstanceType(name, this);
		}

		CSharpInstance *create() { return new T(); }
		void release(CSharpInstance *inst) { delete inst; }
	};

}

#endif