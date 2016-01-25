// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITORBACKEND_CSHARPINSTANCE_H
#define EDITORBACKEND_CSHARPINSTANCE_H

#include <vector>

#include "engine/stream/CSharpInputStream.h"
#include "engine/stream/CSharpBufferedOutputStream.h"
#include "engine/util/Bind.h"

namespace editor {

	class CSharpInstance
	{
	public:
		CSharpInstance() {}

		~CSharpInstance()
		{
			//Destroy binds
			for (unsigned i = 0; i < binds.size(); ++i)
				delete binds[i];
		}

		virtual bool init() = 0;
		virtual void uninit() = 0;

	private:
		engine::stream::CSharpBufferedOutputStream callBufferStream;

		std::vector<engine::util::BindBase*> binds;

		String name;

	protected:
		template <typename ClassT> 
		void registerEvent(const char *name, ClassT *obj, void (ClassT::*func)())
		{
			engine::util::Bind<ClassT> *bind = new engine::util::Bind<ClassT>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			binds.push_back(bind);
		}

		template <typename ClassT, typename T1>
		void registerEvent(const char *name, ClassT *obj, void (ClassT::*func)(T1))
		{
			engine::util::Bind_1<ClassT, T1> *bind = new engine::util::Bind_1<ClassT, T1>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			binds.push_back(bind);
		}

		template <typename ClassT, typename T1, typename T2>
		void registerEvent(const char *name, ClassT *obj, void (ClassT::*func)(T1, T2))
		{
			engine::util::Bind_2<ClassT, T1, T2> *bind = new engine::util::Bind_2<ClassT, T1, T2>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			binds.push_back(bind);
		}

		template <typename ClassT, typename T1, typename T2, typename T3>
		void registerEvent(const char *name, ClassT *obj, void (ClassT::*func)(T1, T2, T3))
		{
			engine::util::Bind_3<ClassT, T1, T2, T3> *bind = new engine::util::Bind_3<ClassT, T1, T2, T3>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			binds.push_back(bind);
		}

		template <typename ClassT, typename T1, typename T2, typename T3, typename T4>
		void registerEvent(const char *name, ClassT *obj, void (ClassT::*func)(T1, T2, T3, T4))
		{
			engine::util::Bind_4<ClassT, T1, T2, T3, T4> *bind = new engine::util::Bind_4<ClassT, T1, T2, T3, T4>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			binds.push_back(bind);
		}

	public:
		void setName(String n) { name = n; }
		const String &getName() { return name; }

		void getCallBuffer(char **buf);

		void handleEvent(String bindName)
		{
			engine::stream::CSharpInputStream strm(NULL);
			handleEvent(bindName, strm);
		}

		void handleEvent(String bindName, engine::stream::CSharpInputStream strm)
		{
			for(unsigned i = 0; i < binds.size(); ++i)
			{
				if(binds[i]->name == bindName)
				{
					binds[i]->call(strm);
					return;
				}
			}
		}

		void finalizeSync();

		void writeInstructionCall();

		void call(String cmd)
		{
			writeInstructionCall();
			DEBUG_PRINT("## " << cmd);
			callBufferStream.write(cmd);
		}

		template <typename T1>
		void call(String cmd, T1 t1)
		{
			writeInstructionCall();
			DEBUG_PRINT("## " << cmd);
			callBufferStream.write(cmd);
			callBufferStream.write(t1);
		}

		template <typename T1, typename T2>
		void call(String cmd, T1 t1, T2 t2)
		{
			writeInstructionCall();
			DEBUG_PRINT("## " << cmd);
			callBufferStream.write(cmd);
			callBufferStream.write(t1);
			callBufferStream.write(t2);
		}

		template <typename T1, typename T2, typename T3>
		void call(String cmd, T1 t1, T2 t2, T3 t3)
		{
			writeInstructionCall();
			DEBUG_PRINT("## " << cmd);
			callBufferStream.write(cmd);
			callBufferStream.write(t1);
			callBufferStream.write(t2);
			callBufferStream.write(t3);
		}

		template <typename T1, typename T2, typename T3, typename T4>
		void call(String cmd, T1 t1, T2 t2, T3 t3, T4 t4)
		{
			writeInstructionCall();
			DEBUG_PRINT("## " << cmd);
			callBufferStream.write(cmd);
			callBufferStream.write(t1);
			callBufferStream.write(t2);
			callBufferStream.write(t3);
			callBufferStream.write(t4);
		}
	};

}

#endif