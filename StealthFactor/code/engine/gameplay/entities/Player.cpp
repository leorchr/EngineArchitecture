#include "engine/gameplay/entities/Player.hpp"

#include "engine/gameplay/components/PlayerInputComponent.h"
#include <engine/gameplay/components/ShapeComponent.h>
#include "engine/gameplay/components/PlayerPhysicsComponent.h"

Player::Player()
{
	shapeComp = std::make_shared<ShapeComponent>(*this, "player");
	
	inputComp = std::make_shared<PlayerInputComponent>(*this);

	physicsComponent = std::make_shared<PlayerPhysicsComponent>(*this);
}

Player::~Player(){}

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