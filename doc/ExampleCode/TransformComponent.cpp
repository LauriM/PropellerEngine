#include "engine/precompiled.h"
#include "engine/scene/TransformComponent.h"

// This class provides good example on serializing data.
// Aka, making sure you can quicksave/quickload the game state.
// This also makes it possible for the future tools(?) to use the object effectively.

namespace engine {
namespace scene {

	DECLARE_CLASS(TransformComponent, engine::component::Component);

	// now declaring the properties defined on the header!
	// these need to be identical for the system to work
	BEGIN_PROPERTIES(TransformComponent);
		DECLARE_PROPERTY(Vec3, Position);
		DECLARE_PROPERTY(Vec3, Direction);
		DECLARE_PROPERTY(float, Scale);
	END_PROPERTIES(TransformComponent);

	void TransformComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		// save properties to stream automatically saves all the properties registered.
		// if you have some other data that for some wierd reason is not a property and you want to save it
		// you can here call strm.write(..) to save it.
		// In that case, you are most likely doing something wrong and should consult the engine developer.

		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void TransformComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		// if you have custom stuff, use strm.read() here in correct order.
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}