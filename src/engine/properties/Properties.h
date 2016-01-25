// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_COMPONENT_PROPERTIES_H
#define ENGINE_COMPONENT_PROPERTIES_H

#include "engine/math/Vector.h"
#include "engine/lang/Handle.h"

typedef int PropellerEnum;

namespace engine {
namespace properties {

	typedef engine::math::Vec2 Vec2;
	typedef engine::math::Vec3 Vec3;

	enum PropertyType
	{
		PropertyTypeUnsigned = 0,
		PropertyTypeSigned,
		PropertyTypeBool,
		PropertyTypeFloat,
		PropertyTypeDouble,
		PropertyTypeString,
		PropertyTypeVec2,
		PropertyTypeVec3,
		PropertyTypeHandle,
		AmountOfPropertyTypes
	};

	#define TYPE_TO_PROP_ENUM_unsigned engine::properties::PropertyTypeUnsigned
	#define TYPE_TO_PROP_ENUM_int engine::properties::PropertyTypeSigned
	#define TYPE_TO_PROP_ENUM_signed engine::properties::PropertyTypeSigned
	#define TYPE_TO_PROP_ENUM_bool engine::properties::PropertyTypeBool
	#define TYPE_TO_PROP_ENUM_float engine::properties::PropertyTypeFloat
	#define TYPE_TO_PROP_ENUM_double engine::properties::PropertyTypeDouble
	#define TYPE_TO_PROP_ENUM_String engine::properties::PropertyTypeString
	#define TYPE_TO_PROP_ENUM_Vec2 engine::properties::PropertyTypeVec2
	#define TYPE_TO_PROP_ENUM_Vec3 engine::properties::PropertyTypeVec3
	#define TYPE_TO_PROP_ENUM_Handle engine::properties::PropertyTypeHandle
	#define TYPE_TO_PROP_ENUM_PropellerEnum engine::properties::PropertyTypeSigned

	typedef engine::lang::Handle Handle;

	union Setter
	{
		void(*_unsigned)(void *, unsigned);
		void(*_signed)(void *, signed);
		void(*_bool)(void *, bool);
		void(*_float)(void *, float);
		void(*_double)(void *, double);
		void(*_String)(void *, String);
		void(*_Vec2)(void *, Vec2);
		void(*_Vec3)(void *, Vec3);
		void(*_Handle)(void *, engine::lang::Handle);
	};

	union Getter
	{
		unsigned(*_unsigned)(void *);
		signed(*_signed)(void *);
		bool(*_bool)(void *);
		float(*_float)(void *);
		double(*_double)(void *);
		String(*_String)(void *);
		Vec2(*_Vec2)(void *);
		Vec3(*_Vec3)(void *);
		engine::lang::Handle(*_Handle)(void *);
	};

	class Property
	{
	protected:
		String name; //Display name for the editors
		PropertyType type;

#ifdef _EDITOR
		bool dirty;
#endif

	public:
		Setter setter;
		Getter getter;
		bool(*isDirtyFuncPtr)(void *);
		void(*clearDirtyFuncPtr)(void *);
		void(*_RefreshHandle)(void *);

		Property(String name, PropertyType type)
			: name(name)
			, type(type)
		{ }

		const String &getName()
		{
			return name;
		}

		PropertyType getType()
		{
			return type;
		}

		void refreshHandle(void *obj)
		{
			assert(this->type == TYPE_TO_PROP_ENUM_Handle);
			_RefreshHandle(obj);
		}

#ifdef _EDITOR
#define SET_DIRTY_FLAG_PROP_SET\
		DEBUG_PRINT("DIRTY FLAG IS DIRTY!");
#else
#define SET_DIRTY_FLAG_PROP_SET\
		DEBUG_PRINT("NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
#endif

	#define PROP_SET(p_type)\
		void set(void *obj, p_type value) {\
			assert(this->type == TYPE_TO_PROP_ENUM_##p_type);\
			setter._##p_type(obj, value);\
		}

	#define PROP_GET(p_type)\
		const p_type get_##p_type(void *obj) const {\
			assert(this->type == TYPE_TO_PROP_ENUM_##p_type);\
			return getter._##p_type(obj);\
		}

	#define PROP_GETSET(p_type)\
		PROP_GET(p_type)\
		PROP_SET(p_type)

		//---

		PROP_GETSET( signed );
		PROP_GETSET( unsigned );
		PROP_GETSET( bool );
		PROP_GETSET( float );
		PROP_GETSET( double );
		PROP_GETSET( String );
		PROP_GETSET( Vec2 );
		PROP_GETSET( Vec3 );
		
		/* Custom properties */

		void set(void *obj, engine::lang::Handle value) {
			assert(this->type == TYPE_TO_PROP_ENUM_Handle);
			setter._Handle(obj, value); //Get the handle ID out
		}

		const engine::lang::Handle get_Handle(void *obj) const {
			assert(this->type == TYPE_TO_PROP_ENUM_Handle);
			return getter._Handle(obj);
		}

		bool isDirty(void *obj) const {
			return isDirtyFuncPtr(obj);
		}

		void clearDirty(void *obj) const {
			return clearDirtyFuncPtr(obj);
		}

	};

	// Convert propertytype to correct getter/setter union member.
	class PropertyUnionHelper
	{
	public:

	#define PROPERTY_SETTER_TYPE(p_var)\
		static void set(engine::properties::Property &prop, void (*func)(void *, p_var)){\
			prop.setter._##p_var = func;\
		}

	#define PROPERTY_GETTER_TYPE(p_var)\
		static void get(engine::properties::Property &prop, p_var (*func)(void *)){\
			prop.getter._##p_var = func;\
		}


	#define PROPERTY_GETSET_TYPE(p_type)\
		PROPERTY_GETTER_TYPE( p_type );\
		PROPERTY_SETTER_TYPE( p_type );\
		//---

		PROPERTY_GETSET_TYPE(unsigned);
		PROPERTY_GETSET_TYPE(signed);
		PROPERTY_GETSET_TYPE(bool);
		PROPERTY_GETSET_TYPE(float);
		PROPERTY_GETSET_TYPE(double);
		PROPERTY_GETSET_TYPE(String);
		PROPERTY_GETSET_TYPE(Vec2);
		PROPERTY_GETSET_TYPE(Vec3);

		/* Custom Properties */
		static void set(engine::properties::Property &prop, void (*func)(void *, engine::lang::Handle)){
			prop.setter._Handle = func;
		}

		static void get(engine::properties::Property &prop, engine::lang::Handle (*func)(void *)){
			prop.getter._Handle = func;
		}

		static void dirtyfunc(engine::properties::Property &prop, bool(*func)(void *)){
			prop.isDirtyFuncPtr = func;
		}

		static void cleardirtyfunc(engine::properties::Property &prop, void(*func)(void *)){
			prop.clearDirtyFuncPtr = func;
		}
	};

	typedef std::vector<Property> PropertyVector;

	// ## CPP RELATED ##

	//Static init add the properties to the propertyvector
	//Creates one copy of the class so that the static property vector can be accessed.
#define BEGIN_PROPERTIES(p_class)\
		typedef p_class ThisClass;\
		class PropertiesHelper##p_class;\
		typedef PropertiesHelper##p_class ThisPropHelperClass;\
		class PropertiesHelper##p_class{\
		\
		public:\
			PropertiesHelper##p_class(){\
			p_class c(NULL); \

	// Creates the "Property" and adds it to the vector
#define DECLARE_PROPERTY(p_type, p_name)\
		engine::properties::Property prop##p_name(TO_STRING(p_name), TYPE_TO_PROP_ENUM_##p_type);\
		engine::properties::PropertyUnionHelper::set(prop##p_name, &ThisClass::set##p_name##Static); \
		engine::properties::PropertyUnionHelper::get(prop##p_name, &ThisClass::get##p_name##Static); \
		engine::properties::PropertyUnionHelper::dirtyfunc(prop##p_name, &ThisClass::isNetworkDirty##p_name##Static); \
		engine::properties::PropertyUnionHelper::cleardirtyfunc(prop##p_name, &ThisClass::clearNetworkDirty##p_name##Static); \
		c.getProperties().push_back(prop##p_name);\

#define DECLARE_PROPERTY_HANDLE(p_type, p_name)\
		engine::properties::Property prop##p_name(TO_STRING(p_name), TYPE_TO_PROP_ENUM_##p_type);\
		engine::properties::PropertyUnionHelper::set(prop##p_name, &ThisClass::set##p_name##Static); \
		engine::properties::PropertyUnionHelper::get(prop##p_name, &ThisClass::get##p_name##Static); \
		engine::properties::PropertyUnionHelper::dirtyfunc(prop##p_name, &ThisClass::isNetworkDirty##p_name##Static); \
		engine::properties::PropertyUnionHelper::cleardirtyfunc(prop##p_name, &ThisClass::clearNetworkDirty##p_name##Static); \
		prop##p_name._RefreshHandle = &ThisClass::handleRefresh##p_name##Static;\
		c.getProperties().push_back(prop##p_name);\

#define END_PROPERTIES(p_class)\
			}/* end of constructor */\
			}; \
		ThisPropHelperClass p_class##___PropertiesHelper;


	// ## HEADER RELATED ##

	//Adds static access for propertyvector
	//This is defined in the Component
#define GENERATE_STATIC_PROPERTY_VECTOR\
		inline engine::properties::PropertyVector& getProperties() const {\
			static engine::properties::PropertyVector staticPropertyVector; \
			return staticPropertyVector; \
			}

	// Network dirty flag for the properties, injected only for Dedicated server builds
#ifdef DEDICATED_SERVER
	#define NETWORK_FLAG(p_name) bool networkDirty##p_name;
	#define NETWORK_SET_DIRTY_FLAG(p_name) networkDirty##p_name = true;

	#define NETWORK_IS_DIRTY(p_name)\
		bool isNetworkDirty##p_name() const { return networkDirty##p_name; }\
		void clearNetworkDirty##p_name() { networkDirty##p_name = false; }\
		static bool isNetworkDirty##p_name##Static(void *obj) {\
			ThisClass* c = (ThisClass*)obj;\
			return c->isNetworkDirty##p_name();\
		}\
		static void clearNetworkDirty##p_name##Static(void *obj) {\
			ThisClass* c = (ThisClass*)obj;\
			c->clearNetworkDirty##p_name();\
		}

#else
	#define NETWORK_FLAG(p_name) ;
	#define NETWORK_SET_DIRTY_FLAG(p_name) ;
	#define NETWORK_IS_DIRTY(p_name)\
		bool isNetworkDirty##p_name() const { return false; }\
		void clearNetworkDirty##p_name() { }\
		static bool isNetworkDirty##p_name##Static(void *obj) { return false; }\
		static void clearNetworkDirty##p_name##Static(void *obj) {};
#endif

	//Creates -> variable
	//        -> getter / setter
	// Double name to fix the getter/setter naming
#define DEFINE_PROPERTY(p_type, p_name, p_uppername)\
		private:\
			p_type p_name; \
			NETWORK_FLAG(p_uppername);\
		public:\
			void set##p_uppername(const p_type &v){ p_name = v; NETWORK_SET_DIRTY_FLAG(p_uppername) } \
			const p_type &get##p_uppername() const { return p_name; }\
			static void set##p_uppername##Static(void *obj, p_type v) {\
				ThisClass* c = (ThisClass*)obj;\
				c->set##p_uppername(v); \
			} \
			static p_type get##p_uppername##Static(void *obj) {\
				ThisClass* c = (ThisClass*)obj;\
				return c->get##p_uppername();\
			}\
			NETWORK_IS_DIRTY(p_uppername)

	//Same as DEFINE_PROPERTY, but allows the user to overwrite the setter
	#define DEFINE_PROPERTY_CUSTOM_SET(p_type, p_name, p_uppername)\
		private:\
			p_type p_name; \
			NETWORK_FLAG(p_uppername);\
		public:\
			const p_type &get##p_uppername() const { return p_name; }\
			static void set##p_uppername##Static(void *obj, p_type v) {\
				ThisClass* c = (ThisClass*)obj;\
				c->set##p_uppername(v);\
			} \
			static p_type get##p_uppername##Static(void *obj) {\
				ThisClass* c = (ThisClass*)obj;\
				return c->get##p_uppername();\
			}\
			NETWORK_IS_DIRTY(p_uppername)

	//Same as DEFINE_PROPERTY, but allows the user to overwrite the getter
	#define DEFINE_PROPERTY_CUSTOM_GET(p_type, p_name, p_uppername)\
		private:\
			p_type p_name; \
			NETWORK_FLAG(p_uppername);\
		public:\
			void set##p_uppername(const p_type &v){ p_name = v; NETWORK_SET_DIRTY_FLAG(p_uppername) } \
			static void set##p_uppername##Static(void *obj, p_type v) {\
				ThisClass* c = (ThisClass*)obj;\
				c->set##p_uppername(v); \
				} \
			static p_type get##p_uppername##Static(void *obj) {\
				ThisClass* c = (ThisClass*)obj;\
				return c->get##p_uppername();\
				} \
				NETWORK_IS_DIRTY(p_uppername)

	/* Custom properties */
	#define DEFINE_PROPERTY_HANDLE(p_name, p_uppername)\
		private:\
			engine::lang::Handle p_name; \
			NETWORK_FLAG(p_uppername);\
		public:\
			void set##p_uppername(engine::lang::Handle v){ p_name = v; NETWORK_SET_DIRTY_FLAG(p_uppername) }; \
			const engine::lang::Handle& get##p_uppername() const { return p_name; };\
			void handleRefresh##p_uppername() { p_name##.refreshHandle(); }\
			static void set##p_uppername##Static(void *obj, engine::lang::Handle v) {\
				ThisClass* c = (ThisClass*)obj;\
				c->set##p_uppername(v); \
			} \
			static engine::lang::Handle get##p_uppername##Static(void *obj) {\
				ThisClass* c = (ThisClass*)obj;\
				return c->get##p_uppername();\
			}\
			static void handleRefresh##p_uppername##Static(void *obj){\
				ThisClass* c = (ThisClass*)obj;\
				c->handleRefresh##p_uppername();\
				DEBUG_PRINT("HandleRefresh!");\
			}\
			NETWORK_IS_DIRTY(p_uppername)

	#define SAVE_PROPERTIES_TO_STREAM(p_strm)\
		engine::properties::PropertyVector props = this->getProperties();\
		engine::properties::savePropertiesToStream(props, p_strm, (void*)this);

	inline void savePropertiesToStream(PropertyVector props, stream::OutputStream<stream::SerializationEndian> &strm, void* obj)
	{
		for (unsigned i = 0; i < props.size(); ++i)
		{
			switch (props[i].getType())
			{
			case PropertyTypeUnsigned:
				strm.write(props[i].get_unsigned(obj));
				break;
			case PropertyTypeSigned:
				strm.write(props[i].get_signed(obj));
				break;
			case PropertyTypeBool:
				strm.write(props[i].get_bool(obj));
				break;
			case PropertyTypeFloat:
				strm.write(props[i].get_float(obj));
				break;
			case PropertyTypeDouble:
				strm.write(props[i].get_double(obj));
				break;
			case PropertyTypeString:
				strm.write(props[i].get_String(obj));
				break;
			case PropertyTypeHandle:
				strm.write(props[i].get_Handle(obj));
				break;
			case PropertyTypeVec2:
				{
					const Vec2 vec = props[i].get_Vec2(obj);
					strm.write(vec.x);
					strm.write(vec.y);
				}
				break;
			case PropertyTypeVec3:
				{
					const Vec3 vec = props[i].get_Vec3(obj);
					strm.write(vec.x);
					strm.write(vec.y);
					strm.write(vec.z);
				}
				break;
			}
		}
	}


	#define LOAD_PROPERTIES_FROM_STREAM(p_strm, p_handleManager)\
		engine::properties::PropertyVector props = this->getProperties();\
		engine::properties::loadPropertiesFromStream(props, p_strm, (void*)this, p_handleManager);

	inline void loadPropertiesFromStream(PropertyVector props, stream::InputStream<stream::SerializationEndian> &strm, void* obj, lang::HandleManager *manager)
	{
		for (unsigned i = 0; i < props.size(); ++i)
		{
			String str;
			Vec2 vec2(0,0);
			Vec3 vec3(0,0,0);
			Handle handle(manager);

			switch (props[i].getType())
			{
			case PropertyTypeUnsigned:
				unsigned uint;
				strm.read(uint);
				props[i].set(obj, uint);
				break;
			case PropertyTypeSigned:
				signed val;
				strm.read(val);
				props[i].set(obj, val);
				break;
			case PropertyTypeBool:
				bool b;
				strm.read(b);
				props[i].set(obj, b);
				break;
			case PropertyTypeFloat:
				float f;
				strm.read(f);
				props[i].set(obj, f);
				break;
			case PropertyTypeDouble:
				double d;
				strm.read(d);
				props[i].set(obj, d);
				break;
			case PropertyTypeString:
				strm.read(str);
				props[i].set(obj, str);
				break;
			case PropertyTypeVec2:
				strm.read(vec2.x);
				strm.read(vec2.y);
				props[i].set(obj, vec2);
				break;
			case PropertyTypeVec3:
				strm.read(vec3.x);
				strm.read(vec3.y);
				strm.read(vec3.z);
				props[i].set(obj, vec3);
				break;
			case PropertyTypeHandle:
				handle.load(strm);
				props[i].set(obj, handle);
				break;
			}
		}
	}

}
}

#endif
