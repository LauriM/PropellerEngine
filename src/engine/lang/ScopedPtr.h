// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_LANG_UNIQUEPTR_H
#define ENGINE_LANG_UNIQUEPTR_H

namespace engine {
namespace lang {

	template <typename T>
	class MoveOnAssign;

	template <typename T>
	class ScopedPtr
	{
	protected:
		T *ptr;
		void reset() { ptr = NULL; }

	public:
		// Copy constructor, move ownership
		ScopedPtr(const ScopedPtr<T> &other)
			: ptr(other.getPtr())
		{ }

		ScopedPtr()
			: ptr(NULL)
		{ }

		ScopedPtr(T *ptr)
			: ptr(ptr)
		{ }

		~ScopedPtr()
		{
			if (ptr == NULL)
				return;

			delete ptr;
		}

		void swap(ScopedPtr<T> &other)
		{
			T *p = other.ptr;
			other.ptr = ptr;
			ptr = p;
		}

		ScopedPtr<T> & operator = (const ScopedPtr<T> &other)
		{
			ptr = other.ptr;
			T* p = const_cast<T*>(other.ptr);
			p = NULL;

			return *this;
		}

		void operator = (T* ptr)
		{
			this->ptr = ptr;
		}

		T * getPtr() const { return ptr; }

		T * operator -> () const
		{
			return ptr;
		}

		T & operator * () const
		{
			return ptr;
		}
	};

}
}

#endif