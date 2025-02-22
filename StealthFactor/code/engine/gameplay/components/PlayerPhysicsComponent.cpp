#include "PlayerPhysicsComponent.h"

#include "engine/Engine.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/physics/PhysicsManager.hpp"
#include "engine/gameplay/entities/Player.hpp"
#include "engine/gameplay/entities/Target.hpp"

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity& entity) : PhysicsComponent(entity)
{
    context = &Engine::getInstance().getContext();

    collisionGeomId = dCreateBox(context->physicsManager->getSpaceId(), GameplayManager::CELL_SIZE * 0.9f, GameplayManager::CELL_SIZE * 0.9f, 1.f);
    dGeomSetData(collisionGeomId, this);
    player = dynamic_cast<Player*>(&entity);
}

PlayerPhysicsComponent::~PlayerPhysicsComponent()
{
}

void PlayerPhysicsComponent::update()
{
    if (player->hasJustMoved())
    {
        auto &position = entity.getPosition();
        dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
        auto collisions = context->physicsManager->getCollisionsWith(collisionGeomId);
        for (auto &geomId : collisions)
        {
            void *data = dGeomGetData(geomId);
            if (!data)
            {
                return;
            }
            
            auto component = reinterpret_cast<PhysicsComponent *>(dGeomGetData(geomId));
		      
            if (component && component->isValid())
            {
                auto targetEntity = dynamic_cast<Target*>(component->getEntity());
                if (targetEntity)
                {
                    context->gameplayManager->loadNextMap();
                }
            }
        }
    }

}
