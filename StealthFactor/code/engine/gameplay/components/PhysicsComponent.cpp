#include "PhysicsComponent.h"
#include "engine/Engine.hpp"
#include "engine/gameplay/Entity.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/physics/PhysicsManager.hpp"
#include <ode/collision.h>

PhysicsComponent::PhysicsComponent(Entity& entity) : Component(entity)
{
    auto context = Engine::getInstance().getContext();
    collisionGeomId = dCreateBox(context.physicsManager->getSpaceId(), GameplayManager::CELL_SIZE * 0.9f, GameplayManager::CELL_SIZE * 0.9f, 1.f);
    dGeomSetData(collisionGeomId, this);
    auto &position = entity.getPosition();
    dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
}

PhysicsComponent::~PhysicsComponent()
{
    if (collisionGeomId)
    {
        dGeomSetData(collisionGeomId, nullptr); // Supprime les données associées
        dGeomDestroy(collisionGeomId);         // Détruit la géométrie
        collisionGeomId = nullptr;
    }
}

void PhysicsComponent::update()
{
    auto &position = entity.getPosition();
    dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
}

bool PhysicsComponent::isValid() const
{
    return collisionGeomId != nullptr;
}
