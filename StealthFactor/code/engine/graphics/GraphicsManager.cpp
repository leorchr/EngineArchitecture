#include <engine/graphics/GraphicsManager.hpp>
#include <engine/gameplay/components/ShapeComponent.h>

#include <cassert>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Event.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/graphics/ShapeList.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/Engine.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <memory>

GraphicsManager::GraphicsManager(std::shared_ptr<sf::RenderWindow> windowP)
{
	sharedWindow = windowP;
	sharedWindow->create(sf::VideoMode{ (unsigned int)WINDOW_WIDTH, (unsigned int)WINDOW_HEIGHT }, "Stealth Factor");
	
	sharedWindow->setVerticalSyncEnabled(true);
	sharedWindow->setFramerateLimit(60);
	
	sf::View view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT });
	sharedWindow->setView(view);

	gm = Engine::getInstance().getContext().gameplayManager;
}

GraphicsManager::~GraphicsManager()
{
	sharedWindow->close();
}

void GraphicsManager::update()
{
	//input::Manager::getInstance().clear();

	// sf::Event event;
	// while (window.pollEvent(event))
	// {
	// 	switch (event.type)
	// 	{
	// 	case sf::Event::Closed:
	// 		Engine::getInstance().exit();
	// 		break;
	//
	// 	case sf::Event::KeyPressed:
	// 		input::Manager::getInstance().onKeyPressed(event.key);
	// 		break;
	//
	// 	case sf::Event::KeyReleased:
	// 		input::Manager::getInstance().onKeyReleased(event.key);
	// 		break;
	//
	// 	default:
	// 		break;
	// 	}
	// }
}

void GraphicsManager::clear()
{
	sharedWindow->clear(sf::Color::Black);

	sf::View view{ gm->getViewCenter(), sf::Vector2f{(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT} };
	sharedWindow->setView(view);
}

void GraphicsManager::draw()
{
	for (auto shape : shapesToDraw)
	{
		if(shape) shape->draw(*sharedWindow);
	}
	
	// for (auto entity : GameplayManager::getInstance().getEntities())
	// {
	// 	if(!entity->isDead) entity->draw(*sharedWindow);
	// }
	
	// for (auto shape : shapeList.getShapes())
	// {
	// 	window.draw(*shape, renderStates);
	// }
}

void GraphicsManager::display()
{
	sharedWindow->display();
}

void GraphicsManager::addShape(ShapeComponent* shapeComponent)
{
	if(shapeComponent)
	{
		shapesToDraw.push_back(shapeComponent);
	}
}

void GraphicsManager::removeShape(ShapeComponent* shapeComponent)
{
	auto it = std::find(shapesToDraw.begin(), shapesToDraw.end(), shapeComponent);
	if (it != shapesToDraw.end()) {
		shapesToDraw.erase(it);
	}
}

bool GraphicsManager::hasFocus() const
{
	return sharedWindow->hasFocus();
}
