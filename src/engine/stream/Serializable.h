// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_STREAM_SERIALIZABLE_H
#define ENGINE_STREAM_SERIALIZABLE_H

#include "engine/stream/OutputStream.h"
#include "engine/stream/InputStream.h"

#include "engine/rtti/Object.h"
#include "engine/rtti/Class.h"

#include <string>

typedef std::string String;

namespace engine {
namespace stream {

	class Serializable : public engine::rtti::Object
	{
	private:
		unsigned handleid;

		DEFINE_CLASS(Serializable);

	public:
		Serializable(void *context);
		~Serializable();

		unsigned getHandleId() { return handleid; }

		virtual void save(stream::OutputStream<stream::SerializationEndian> &strm) const = 0;
		virtual void load(stream::InputStream<stream::SerializationEndian> &strm) = 0;
	};

}
}

#endif
