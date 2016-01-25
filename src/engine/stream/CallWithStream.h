// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_CALLWITHSTREAM_H
#define ENGINE_STREMA_CALLWITHSTREAM_H

#include "engine/stream/InputStream.h"

namespace engine {
namespace stream {

	void testFunction(int);

	template <typename T, typename Endianess>
	class CallWithStream {};

	template <typename R, typename Endianess>
	class CallWithStream<R(*)(), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R(*func)(), InputStream<Endianess> &strm) const
		{
			return func();
		}
	};

	template <typename R, typename T1, typename Endianess>
	class CallWithStream<R (*)(T1), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R (*func)(T1), InputStream<Endianess> &strm) const
		{
			T1 a1;
			strm.read(a1);
			return func(a1);
		}
	};

	template <typename R, typename T1, typename T2, typename Endianess>
	class CallWithStream<R (*)(T1,T2), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R (*func)(T1,T2), InputStream<Endianess> &strm) const
		{
			T1 a1;
			T2 a2;
			strm.read(a1);
			strm.read(a2);
			return func(a1,a2);
		}
	};

	template <typename R, typename T1, typename T2, typename T3, typename Endianess>
	class CallWithStream<R (*)(T1,T2,T3), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R (*func)(T1,T2,T3), InputStream<Endianess> &strm) const
		{
			T1 a1;
			T2 a2;
			T3 a3;
			strm.read(a1);
			strm.read(a2);
			strm.read(a3);
			return func(a1,a2,a3);
		}
	};

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename Endianess>
	class CallWithStream<R (*)(T1,T2,T3,T4), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R (*func)(T1,T2,T3,T4), InputStream<Endianess> &strm) const
		{
			T1 a1;
			T2 a2;
			T3 a3;
			T4 a4;
			strm.read(a1);
			strm.read(a2);
			strm.read(a3);
			strm.read(a4);
			return func(a1,a2,a3,a4);
		}
	};

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename Endianess>
	class CallWithStream<R (*)(T1,T2,T3,T4,T5), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R (*func)(T1,T2,T3,T4,T5), InputStream<Endianess> &strm) const
		{
			T1 a1;
			T2 a2;
			T3 a3;
			T4 a4;
			T5 a5;
			strm.read(a1);
			strm.read(a2);
			strm.read(a3);
			strm.read(a4);
			strm.read(a5);
			return func(a1,a2,a3,a4,a5);
		}
	};

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename Endianess>
	class CallWithStream<R (*)(T1,T2,T3,T4,T5,T6), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (R (*func)(T1,T2,T3,T4,T5,T6), InputStream<Endianess> &strm) const
		{
			T1 a1;
			T2 a2;
			T3 a3;
			T4 a4;
			T5 a5;
			T6 a6;
			strm.read(a1);
			strm.read(a2);
			strm.read(a3);
			strm.read(a4);
			strm.read(a5);
			strm.read(a6);
			return func(a1,a2,a3,a4,a5,a6);
		}
	};

	template <typename ClassT, typename R, typename Endianess>
	class CallWithStream<R(ClassT::*)(), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (ClassT *this_, R(ClassT::*func)(), InputStream<Endianess> &strm) const
		{
			return (this_->*func)();
		}
	};

	template <typename ClassT, typename R, typename T1, typename Endianess>
	class CallWithStream<R(ClassT::*)(T1), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (ClassT *this_, R (ClassT::*func)(T1), InputStream<Endianess> &strm) const
		{
			T1 a1; strm.read(a1);
			return (this_->*func)(a1);
		}
	};

	template <typename ClassT, typename R, typename T1, typename T2, typename Endianess>
	class CallWithStream<R(ClassT::*)(T1, T2), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (ClassT *this_, R (ClassT::*func)(T1, T2), InputStream<Endianess> &strm) const
		{
			T1 a1; strm.read(a1);
			T2 a2; strm.read(a2);
			return (this_->*func)(a1,a2);
		}
	};

	template <typename ClassT, typename R, typename T1, typename T2, typename T3, typename Endianess>
	class CallWithStream<R(ClassT::*)(T1, T2, T3), Endianess>
	{
	public:
		typedef R Ret;

		R operator () (ClassT *this_, R (ClassT::*func)(T1, T2, T3), InputStream<Endianess> &strm) const
		{
			T1 a1; strm.read(a1);
			T2 a2; strm.read(a2);
			T3 a3; strm.read(a3);
			return (this_->*func)(a1,a2,a3);
		}
	};

	template <typename T, typename Endianess>
	typename CallWithStream<T, Endianess>::Ret callFunction(T func, InputStream<Endianess> &strm)
	{
		CallWithStream<T, Endianess> callWithStream;
		return callWithStream(func, strm);
	};

	template <typename ClassT, typename FuncT, typename Endianess>
	typename CallWithStream<FuncT, Endianess>::Ret callFunction(ClassT *this_, FuncT func, InputStream<Endianess> &strm)
	{
		CallWithStream<FuncT, Endianess> callWithStream;
		return callWithStream(this_, func, strm);
	}

	void testFunction(int value)
	{
		for(int i = 0; i < value; ++i)
		{
			DEBUG_PRINT("HAHA");
		}
	}

	void tripleTest(int x,int y, std::string name)
	{
		printf("[%i,%i] %s\n",x,y, name.c_str());
	}

}
}

#endif
