#include "Component.h"
#include "engine/gameplay/Entity.hpp"

Component::Component(Entity& entity) : entity(entity) {}

Component::~Component()
{
	entity.removeComponent(shared_from_this());
}

void Component::initialize()
{
	entity.addComponent(shared_from_this());
}