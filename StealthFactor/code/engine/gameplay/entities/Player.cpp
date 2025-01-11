#include "engine/gameplay/entities/Player.hpp"
#include "engine/gameplay/components/PlayerInputComponent.h"
#include <engine/gameplay/components/ShapeComponent.h>

#include "Target.hpp"
#include "engine/gameplay/components/PhysicsComponent.h"
#include "engine/Engine.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/physics/PhysicsManager.hpp"

Player::Player()
{
	std::shared_ptr<Component> comp = std::make_shared<ShapeComponent>(*this, "player");
	comp->initialize();
	
	inputComp = std::make_shared<PlayerInputComponent>(*this);
	inputComp->initialize();

	context = &Engine::getInstance().getContext();

	collisionGeomId = dCreateBox(context->physicsManager->getSpaceId(), context->gameplayManager->CELL_SIZE * 0.9f, context->gameplayManager->CELL_SIZE * 0.9f, 1.f);
	dGeomSetData(collisionGeomId, this);
}

void Player::update()
{
	inputComp->update();

	
	if (justMoved)
	{
		dGeomSetPosition(collisionGeomId, getPosition().x, getPosition().y, 0);
	}
	
	auto collisions = context->physicsManager->getCollisionsWith(collisionGeomId);
	for (auto &geomId : collisions)
	{
		auto component = reinterpret_cast<PhysicsComponent *>(dGeomGetData(geomId));
		
		if (component)
		{
			auto targetEntity = dynamic_cast<Target*>(component->getEntity());
			if (targetEntity)
			{
				context->gameplayManager->loadNextMap();
			}
		}
	}
}

bool Player::hasJustMoved() const
{
	return justMoved;
}

void Player::setJustMoved(bool pJustMoved)
{
	justMoved = pJustMoved;
}
