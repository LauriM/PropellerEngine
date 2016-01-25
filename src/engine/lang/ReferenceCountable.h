// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_LANG_REFERENCECOUNTABLE_H
#define ENGINE_LANG_REFERENCECOUNTABLE_H

namespace engine {
namespace lang {

	class ReferenceCountable
	{
	private:
		unsigned ref;

	public:
		ReferenceCountable()
			: ref(0)
		{}

		void addReference() { ++ref;  }


		const bool removeReference()
		{
			return (--ref == 0);
		}
		
	};

}
}

#endif