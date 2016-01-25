// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_UTIL_BIND_H
#define ENGINE_UTIL_BIND_H

#include "engine/stream/CSharpInputStream.h"

namespace engine {
namespace util {

	struct BindBase
	{
		String name;

		virtual void call(engine::stream::InputStream<stream::NativeEndian> inputStream) = 0;
		virtual void call(engine::stream::CSharpInputStream strm) = 0;
		virtual void call() {};
		virtual void callVoid(void*) {};
	};

	template <typename ClassT>
	struct Bind : public BindBase
	{
		ClassT *obj;
		void (ClassT::*func)();

		void call(engine::stream::InputStream<stream::NativeEndian> strm)
		{
			(obj->*func)();
		}

		void call(engine::stream::CSharpInputStream strm)
		{
			(obj->*func)();
		}

		void call()
		{
			(obj->*func)();
		}
	};

	template <typename ClassT, typename T1>
	struct Bind_1 : public BindBase
	{
		ClassT *obj;
		void (ClassT::*func)(T1);

		void call(engine::stream::InputStream<stream::NativeEndian> strm)
		{
			T1 t1;
			strm.read(t1);
			(obj->*func)(t1);
		}

		void call(engine::stream::CSharpInputStream strm)
		{
			T1 t1;
			strm.read(t1);
			(obj->*func)(t1);
		}

		void call(T1 t1)
		{
			(obj->*func)(t1);
		}
	};

	template <typename ClassT, typename T1, typename T2>
	struct Bind_2 : public BindBase
	{
		ClassT *obj;
		void (ClassT::*func)(T1, T2);

		void call(engine::stream::InputStream<stream::NativeEndian> strm)
		{
			T1 t1;
			T2 t2;
			strm.read(t1);
			strm.read(t2);
			(obj->*func)(t1, t2);
		}

		void call(engine::stream::CSharpInputStream strm)
		{
			T1 t1;
			T2 t2;
			strm.read(t1);
			strm.read(t2);
			(obj->*func)(t1, t2);
		}

		void call(T1 t1, T2 t2)
		{
			(obj->*func)(t1, t2);
		}
	};

	template <typename ClassT, typename T1, typename T2, typename T3>
	struct Bind_3 : public BindBase
	{
		ClassT *obj;
		void (ClassT::*func)(T1, T2, T3);

		void call(engine::stream::InputStream<stream::NativeEndian> strm)
		{
			T1 t1;
			T2 t2;
			T3 t3;
			strm.read(t1);
			strm.read(t2);
			strm.read(t3);
			(obj->*func)(t1, t2, t3);
		}
	
		void call(engine::stream::CSharpInputStream strm)
		{
			T1 t1;
			T2 t2;
			T3 t3;
			strm.read(t1);
			strm.read(t2);
			strm.read(t3);
			(obj->*func)(t1, t2, t3);
		}

		void call(T1 t1, T2 t2, T3 t3)
		{
			(obj->*func)(t1, t2, t3);
		}
	};

	template <typename ClassT, typename T1, typename T2, typename T3, typename T4>
	struct Bind_4 : public BindBase
	{
		ClassT *obj;
		void (ClassT::*func)(T1, T2, T3, T4);

		void call(engine::stream::InputStream<stream::NativeEndian> strm)
		{
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			strm.read(t1);
			strm.read(t2);
			strm.read(t3);
			strm.read(t4);
			(obj->*func)(t1, t2, t3, t4);
		}

		void call(engine::stream::CSharpInputStream strm)
		{
			T1 t1;
			T2 t2;
			T3 t3;
			T4 t4;
			strm.read(t1);
			strm.read(t2);
			strm.read(t3);
			strm.read(t4);
			(obj->*func)(t1, t2, t3, t4);
		}

		void call(T1 t1, T2 t2, T3 t3, T4 t4)
		{
			(obj->*func)(t1, t2, t3, t4);
		}
	};

}
}

#endif