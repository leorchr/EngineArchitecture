#include "ShapeComponent.h"
#include "engine/Engine.hpp"
#include "engine/gameplay/Entity.hpp"
#include "engine/graphics/GraphicsManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

ShapeComponent::ShapeComponent(Entity& entityP, std::string shapeName) : Component(entityP)
{
	if(shapeList.load(shapeName))
	{
		graphicsManager = Engine::getInstance().getContext().graphicsManager;
		graphicsManager->addShape(this);
	}
}

ShapeComponent::~ShapeComponent()
{
	if(Engine::getInstance().getContext().graphicsManager)
	{
		Engine::getInstance().getContext().graphicsManager->removeShape(this);
	}
}

void ShapeComponent::draw(sf::RenderWindow& window)
{
	for(auto shape : shapeList.getShapes())
	{
		window.draw(*shape, entity.getTransform());
	}
}