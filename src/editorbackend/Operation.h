// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_OPERATION_H
#define EDITOR_OPERATION_H

#include "editorbackend/CSharp/CSharpInstance.h"

namespace editor {

	enum AddRemoveOperationType
	{
		OPERATION_ADD = 0,
		OPERATION_REMOVE
	};

	class Operation
	{
	private:
		String name;
		String desc;

	protected:
		CSharpInstance *instance; //in what instance the operation is happening?

	public:
		Operation(const String &name, const String &desc, CSharpInstance *instance)
			: name(name)
			, desc(desc)
			, instance(instance)
		{ }

		virtual bool execute() = 0;
		virtual bool revert() = 0;

		const String &getName() const { return name; }
		const String &getDesc() const { return desc; }
	};

}

#endif