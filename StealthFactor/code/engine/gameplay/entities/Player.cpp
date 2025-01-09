#include "engine/gameplay/entities/Player.hpp"
#include "engine/gameplay/components/PlayerInputComponent.h"
#include <engine/gameplay/components/ShapeComponent.h>

Player::Player()
{
	std::shared_ptr<Component> comp = std::make_shared<ShapeComponent>(*this, "player");
	comp->initialize();
	
	inputComp = std::make_shared<PlayerInputComponent>(*this);
	inputComp->initialize();
	//collisionGeomId = dCreateBox(physics::Manager::getInstance().getSpaceId(), gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f, 1.f);
	//dGeomSetData(collisionGeomId, this);
}

void Player::update()
{
	inputComp->update();
	// if (justMoved)
	// {
	// 	setPosition(position);
	// 	setRotation(rotation);
	//
	// 	dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
	// }
	//
	// auto collisions = physics::Manager::getInstance().getCollisionsWith(collisionGeomId);
	// for (auto &geomId : collisions)
	// {
	// 	auto entity = reinterpret_cast<Entity *>(dGeomGetData(geomId));
	// 	auto targetEntity = dynamic_cast<entities::Target *>(entity);
	// 	if (targetEntity)
	// 	{
	// 		gameplay::Manager::getInstance().loadNextMap();
	// 	}
	// }
}

bool Player::hasJustMoved() const
{
	return justMoved;
}