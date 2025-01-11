#include "Component.h"
#include "engine/gameplay/Entity.hpp"

Component::Component(Entity& entity) : entity(entity) {}

Component::~Component()
{
}

Entity* Component::getEntity()
{
	return &entity;
}