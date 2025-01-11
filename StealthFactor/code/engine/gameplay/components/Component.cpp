#include "Component.h"
#include "engine/gameplay/Entity.hpp"

Component::Component(Entity& entity) : entity(entity) {}

Component::~Component()
{
}

void Component::initialize()
{
	entity.addComponent(shared_from_this());
}

Entity* Component::getEntity()
{
	return &entity;
}