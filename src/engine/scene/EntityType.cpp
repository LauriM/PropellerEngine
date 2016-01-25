// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/scene/EntityType.h"
#include "engine/properties/Properties.h"
#include "engine/scene/ComponentType.h"

#include <json/json.h>

#include "engine/file/FileData.h"

namespace engine {
namespace scene {

	void EntityType::loadFromFile(file::File file)
	{
		PROFILE;

		engine::stream::InputStream<engine::stream::NativeEndian> typeStream((void*)file->getRawData());

		void *dataBuffer = malloc(file->getSize());

		typeStream.read(dataBuffer, file->getSize());

		loadFromJson(String((char*)dataBuffer));

		free(dataBuffer);
	}

	void EntityType::loadFromJson(const String &str)
	{
		PROFILE;

		Json::Value root;
		Json::Reader reader;

		reader.parse(str, root);

		unsigned componentCount = root[0].size();

		Json::Value compList = root[0];
		for (unsigned i = 0; i < componentCount; ++i)
		{
			Json::Value compValue = compList[i];

			ComponentType comp;
			comp.setName(compValue[0].asString());

			//Parse the properties for the component

			Json::Value propertyList = compValue[1];

			for (unsigned z = 0; z < propertyList.size(); ++z)
			{
				Json::Value propValue = propertyList[z];

				//Property contains following data:
				// 0 -> propertyName
				// 1 -> type enum
				// 2 -> data
				properties::PropertyType propType = properties::PropertyType(propValue[1].asUInt());

				PropertyType prop;
				prop.name = propValue[0].asString();

				prop.type = propType;

				//Add the variable into it
				switch(propType)
				{
				default:
					DEBUG_PRINT("Type is not yet supported!");
					DEBUG_BREAK;
					break;
				case properties::PropertyTypeUnsigned:
					prop.value.valueUnsigned = propValue[2].asUInt();
					break;
				case properties::PropertyTypeSigned:
					prop.value.valueSigned = propValue[2].asInt();
					break;
				case properties::PropertyTypeBool:
					prop.value.valueBool = propValue[2].asBool();
					break;
				case properties::PropertyTypeFloat:
					prop.value.valueFloat = propValue[2].asFloat();
					break;
				case properties::PropertyTypeDouble:
					prop.value.valueDouble = propValue[2].asDouble();
					break;
				case properties::PropertyTypeString:
					prop.valueString = propValue[2].asString();
					break;
				case properties::PropertyTypeVec2:
					DEBUG_BREAK; //TODO: Vec2 not yet implemented for json serialization!
					break;
				}

				comp.getPropertyTypeVectorPtr()->push_back(prop);
			}

			components.push_back(comp);
		}
	}

	String EntityType::saveToJson() const
	{
		PROFILE;

		Json::Value root;

		Json::Value compList;

		for (unsigned i = 0; i < components.size(); ++i)
		{
			Json::Value comp;

			comp.append(components[i].getName());

			Json::Value props;

			const scene::PropertyTypeVector propertyVector = components[i].getPropertyTypeVector();
			for (unsigned q = 0; q < propertyVector.size(); ++q)
			{
				Json::Value prop;

				prop.append(propertyVector[q].name);
				prop.append(propertyVector[q].type);

				switch(propertyVector[q].type)
				{
				default:
					DEBUG_PRINT("NOT IMPLEMENTED"); DEBUG_BREAK;
					break;
				case properties::PropertyTypeSigned:
					prop.append(propertyVector[q].value.valueSigned);
					break;
				case properties::PropertyTypeUnsigned:
					prop.append(propertyVector[q].value.valueUnsigned);
					break;
				case properties::PropertyTypeString:
					prop.append(propertyVector[q].valueString);
					break;
				}

				props.append(prop);
			}

			comp.append(props);
			compList.append(comp);
		}

		root.append(compList);

		Json::StyledWriter writer;

		return writer.write(root);
	}

}
}