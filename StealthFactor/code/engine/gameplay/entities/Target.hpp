#pragma once

#include <ode/collision.h>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/Entity.hpp>

class Target : public Entity
{
public:
	Target();
	~Target();

	virtual void update() override;

private:
	ShapeList shapeList;
	dGeomID collisionGeomId;
};