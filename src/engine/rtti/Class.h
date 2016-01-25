// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RTTI_CLASS_H
#define ENGINE_RTTI_CLASS_H

#include <boost/unordered_map.hpp>


//TODO: Major refactor here! Duplicated code!

PROPELLER_FORWARD_DECLARE_1(engine, SystemBase);

#define DEFINE_CLASS(p_class)\
	public:\
		typedef p_class ThisClass;\
		engine::rtti::Class *getTypeInfo();\
		static engine::rtti::Class *getStaticTypeInfo();

#ifdef _EDITOR
// Versions with the path embedded

#define CREATE_TYPEINFO_BASECLASS(p_class)\
	engine::rtti::Class p_class##TypeInfo(TO_STRING(p_class), NULL, sizeof(p_class), TO_STRING(__FILE__) );

#define CREATE_TYPEINFO_CLASS(p_class, p_baseclass)\
	engine::rtti::Class p_class##TypeInfo(TO_STRING(p_class), p_baseclass::getStaticTypeInfo(), sizeof(p_class), TO_STRING(__FILE__) );

#else
// No path info for these

#define CREATE_TYPEINFO_BASECLASS(p_class)\
	engine::rtti::Class p_class##TypeInfo(TO_STRING(p_class), NULL, sizeof(p_class));

#define CREATE_TYPEINFO_CLASS(p_class, p_baseclass)\
	engine::rtti::Class p_class##TypeInfo(TO_STRING(p_class), p_baseclass::getStaticTypeInfo(), sizeof(p_class) );

#endif

#define DECLARE_BASE_CLASS(p_class)\
	CREATE_TYPEINFO_BASECLASS(p_class);\
	engine::rtti::Class *p_class::getTypeInfo()\
	{\
		return &p_class##TypeInfo;\
	}\
	engine::rtti::Class *p_class::getStaticTypeInfo()\
	{\
		return &p_class##TypeInfo;\
	}\
	class p_class##Factory\
	{\
	public:\
		p_class##Factory()\
		{\
			p_class##TypeInfo.setClassFactory(NULL);\
		}\
	};\
	p_class##Factory staticInit##p_class##Factory;

#define DECLARE_CLASS(p_class, p_baseclass)\
	CREATE_TYPEINFO_CLASS(p_class, p_baseclass);\
	engine::rtti::Class *p_class::getTypeInfo()\
	{\
		return &p_class##TypeInfo;\
	}\
	engine::rtti::Class *p_class::getStaticTypeInfo()\
	{\
		return &p_class##TypeInfo;\
	}\
	class p_class##Factory\
	{\
	public:\
		p_class##Factory()\
		{\
			p_class##TypeInfo.setClassFactory(&p_class##Factory::generate);\
		}\
		static engine::rtti::Object *generate(void *ptr)\
		{\
			return new p_class(ptr);\
		}\
	};\
	p_class##Factory staticInit##p_class##Factory;

#define DECLARE_ABSTRACT_CLASS(p_class, p_baseclass)\
	CREATE_TYPEINFO_CLASS(p_class, p_baseclass);\
	engine::rtti::Class *p_class::getTypeInfo()\
	{\
		return &p_class##TypeInfo;\
	}\
	engine::rtti::Class *p_class::getStaticTypeInfo()\
	{\
		return &p_class##TypeInfo;\
	}\
	class p_class##Factory\
	{\
	public:\
		p_class##Factory()\
		{\
			p_class##TypeInfo.setClassFactory(NULL);\
		}\
	};\
	p_class##Factory staticInit##p_class##Factory;

namespace engine {
namespace rtti {

	class Object;
	class Class;

	typedef boost::unordered_map<String, Class*> ClassSet;

	extern ClassSet *g_classSet;

	static ClassSet &getClassSet()
	{
		if (g_classSet == NULL)
			g_classSet = new ClassSet();

		return *g_classSet;
	}

	class Class
	{
	private:
		Object *(*classFactory)(void *);
			
	protected:
		String typeName;
		Class *baseClass;
		size_t size;

#ifdef _EDITOR
		String sourcePath;
#endif

	public:
#ifdef _EDITOR
		Class(String typeName, Class *baseClass, size_t size, String sourcePath)
			: typeName(typeName)
			, baseClass(baseClass)
			, size(size)
			, sourcePath(sourcePath)
			, classFactory(NULL)
		{
			getClassSet()[typeName] = this;
		}

		const String &getSourcePath() const { return sourcePath; }
#endif

		Class(String typeName, Class *baseClass, size_t size)
			: typeName(typeName)
			, baseClass(baseClass)
			, size(size)
			, classFactory(NULL)
		{
			getClassSet()[typeName] = this;
		}

		Object *generate()
		{
			if (classFactory == NULL)
			{
				LOG_ERROR("Class " << typeName  <<" cannot be generated!");
				return NULL;
			}

			LOG_WARNING("Generating object without context!");
			return classFactory(NULL);
		}

		Object *generate(void *context)
		{
			if (classFactory == NULL)
			{
				LOG_ERROR("Class " << typeName << " cannot be generated!");
				return NULL;
			}

			return classFactory(context);
		}

		void setClassFactory(Object *(*gen)(void*)) { classFactory = gen; }

		const String &getTypeName() const { return typeName; }
		const Class *getBaseClass() const { return baseClass; }
		const size_t getSize() const { return size; }

		void *getClassFactory() { return (void*)classFactory; }

		// Only use during rcc++
		void setBaseClass(const Class *base) { baseClass = (Class*)base; }
	};


}
}

#endif