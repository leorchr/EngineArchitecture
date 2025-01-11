#include "engine/gameplay/entities/Player.hpp"

#include "engine/gameplay/components/PlayerInputComponent.h"
#include <engine/gameplay/components/ShapeComponent.h>
#include "engine/gameplay/components/PlayerPhysicsComponent.h"

Player::Player()
{
	std::shared_ptr<Component> comp = std::make_shared<ShapeComponent>(*this, "player");
	comp->initialize();
	
	inputComp = std::make_shared<PlayerInputComponent>(*this);
	inputComp->initialize();

	physicsComponent = std::make_shared<PlayerPhysicsComponent>(*this);
	physicsComponent->initialize();
}

void Player::update()
{
	inputComp->update();
	physicsComponent->update();
}

bool Player::hasJustMoved() const
{
	return justMoved;
}

void Player::setJustMoved(bool pJustMoved)
{
	justMoved = pJustMoved;
}