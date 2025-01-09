#pragma once
#include "engine/gameplay/components/Component.h"
#include "engine/graphics/ShapeList.hpp"
#include <memory>

namespace sf {
	class RenderWindow;
}

class ShapeComponent : public Component
{
public:
	ShapeComponent(class Entity& entity, std::string shapeName);
	~ShapeComponent();
	virtual void draw(sf::RenderWindow& window);
private:
	ShapeList shapeList;

	std::shared_ptr<class GraphicsManager> graphicsManager;
};
