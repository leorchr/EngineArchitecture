#include "engine/gameplay/entities/Player.hpp"

#include "engine/gameplay/components/PlayerInputComponent.h"
#include <engine/gameplay/components/ShapeComponent.h>
#include "engine/gameplay/components/PlayerPhysicsComponent.h"

Player::Player()
{
	shapeComp = std::make_shared<ShapeComponent>(*this, "player");
	shapeComp->initialize();
	
	inputComp = std::make_shared<PlayerInputComponent>(*this);
	inputComp->initialize();

	physicsComponent = std::make_shared<PlayerPhysicsComponent>(*this);
	physicsComponent->initialize();
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