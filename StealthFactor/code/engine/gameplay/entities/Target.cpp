#include "Target.hpp"
#include <SFML/Graphics.hpp>
#include "engine/gameplay/components/ShapeComponent.h"

Target::Target()
{
	std::shared_ptr<Component> comp = std::make_shared<ShapeComponent>(*this, "target");
	comp->initialize();

	//collisionGeomId = dCreateBox(physics::Manager::getInstance().getSpaceId(), gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f, 1.f);
	//dGeomSetData(collisionGeomId, this);
}

Target::~Target()
{
	//dGeomDestroy(collisionGeomId);
}

void Target::update()
{
	//auto &position = getPosition();
	//dGeomSetPosition(collisionGeomId, position.x, position.y, 0);
}
