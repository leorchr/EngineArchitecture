#include "Target.hpp"
#include "engine/gameplay/components/PhysicsComponent.h"
#include "engine/gameplay/components/ShapeComponent.h"


Target::Target()
{
	std::shared_ptr<Component> comp = std::make_shared<ShapeComponent>(*this, "target");
	comp->initialize();
	
	physicsComponent = std::make_shared<PhysicsComponent>(*this);
	physicsComponent->initialize();
}

Target::~Target(){}

void Target::update()
{
	physicsComponent->update();
}