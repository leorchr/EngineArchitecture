#include "Target.hpp"
#include "engine/gameplay/components/PhysicsComponent.h"
#include "engine/gameplay/components/ShapeComponent.h"


Target::Target()
{
	shapeComp = std::make_shared<ShapeComponent>(*this, "target");
	
	physicsComponent = std::make_shared<PhysicsComponent>(*this);
}

Target::~Target(){}

void Target::update()
{
	physicsComponent->update();
}