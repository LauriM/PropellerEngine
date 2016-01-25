#include "catch.hpp"

#include "engine/precompiled.h"

#include "engine/memory/BlockPoolAllocator.h"

#include "engine/scene/TransformComponent.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/scene/CameraComponent.h"

using namespace engine;
using namespace engine::lang;


TEST_CASE("BlockPoolAllocator", "[blockallocator]")
{
	BlockPoolAllocator *allocator = new BlockPoolAllocator(); // prevents the leak detector to break the unittest, by leaking the allocator itself (HACK, TODO)

	size_t sizeTransform = sizeof(scene::TransformComponent);
	size_t sizeRigid = sizeof(physics::Box2DRigidBodyComponent);
	size_t sizeCamera = sizeof(scene::CameraComponent);

	size_t prkl = physics::Box2DRigidBodyComponent::getStaticTypeInfo()->getSize();

	physics::Box2DRigidBodyComponent *comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);
	comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);
	comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);
	comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);
	comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);
	comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);
	comp = (physics::Box2DRigidBodyComponent*)allocator->allocate(prkl);

	uint32_t *dummy;

	uint32_t *odd1 = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*odd1 = 0x00000000;

	dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*dummy = 0xffffffff;

	uint32_t *odd2 = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*odd2 = 0x00000000;

	dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*dummy = 0xffffffff;

	allocator->free(odd2);
	allocator->free(odd1);

	dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*dummy = 0xffffffff;

	dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*dummy = 0xffffffff;

	for (unsigned i = 0; i < 150; ++i)
	{
		dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
		*dummy = 0xffffffff;
	}

	dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*dummy = 0x00000000;

	dummy = (uint32_t*)allocator->allocate(sizeof(uint32_t));
	*dummy = 0xffffffff;

	allocator->free(dummy);

}
