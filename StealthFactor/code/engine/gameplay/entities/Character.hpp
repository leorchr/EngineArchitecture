#pragma once

#include <ode/collision.h>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/Entity.hpp>

class Character : public Entity
{
public:
	Character();
	virtual ~Character();

protected:
	ShapeList shapeList;

	bool isWalking{ false };
};
