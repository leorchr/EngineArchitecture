#include "Target.hpp"
#include <SFML/Graphics.hpp>

#include "engine/Engine.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/gameplay/components/ShapeComponent.h"
#include "engine/physics/PhysicsManager.hpp"

Target::Target()
{
	std::shared_ptr<Component> comp = std::make_shared<ShapeComponent>(*this, "target");
	comp->initialize();

	auto context = Engine::getInstance().getContext();
	collisionGeomId = dCreateBox(context.physicsManager->getSpaceId(), context.gameplayManager->CELL_SIZE * 0.9f, context.gameplayManager->CELL_SIZE * 0.9f, 1.f);
	dGeomSetData(collisionGeomId, this);
}

Target::~Target()
{
	dGeomDestroy(collisionGeomId);
}

void Target::update()
{
	auto &position = getPosition();
	dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
}
