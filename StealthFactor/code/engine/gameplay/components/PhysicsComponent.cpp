#include "PhysicsComponent.h"

#include <ode/collision.h>

#include "engine/Engine.hpp"
#include "engine/gameplay/Entity.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/physics/PhysicsManager.hpp"

PhysicsComponent::PhysicsComponent(Entity& entity) : Component(entity)
{
    auto context = Engine::getInstance().getContext();
    collisionGeomId = dCreateBox(context.physicsManager->getSpaceId(), context.gameplayManager->CELL_SIZE * 0.9f, context.gameplayManager->CELL_SIZE * 0.9f, 1.f);
    dGeomSetData(collisionGeomId, this);
}

PhysicsComponent::~PhysicsComponent()
{
    dGeomDestroy(collisionGeomId);
}

void PhysicsComponent::update()
{
    auto &position = entity.getPosition();
    dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
}
