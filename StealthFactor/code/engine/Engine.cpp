#include "engine/Engine.hpp"

#include <cassert>
#include <iostream>
#include <pugixml/pugixml.hpp>
#include <SFML/System.hpp>

#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <engine/input/InputManager.hpp>

#include "physics/PhysicsManager.hpp"

Engine *Engine::instance = nullptr;

void Engine::loadConfiguration()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("configuration.xml");

	if (result)
	{
		assert(!doc.empty());
		auto configuration = doc.first_child();
		startMap = configuration.child_value("start_map");
	}
	else
	{
		std::cerr << "Configuration parsed with errors." << std::endl;
		std::cerr << "Error description: " << result.description() << std::endl;
		std::cerr << "Error offset: " << result.offset << std::endl;
	}
}

void Engine::run()
{
	running = true;
	context = new Context();
	
	context->gameplayManager = std::make_shared<GameplayManager>();
	std::shared_ptr<class sf::RenderWindow> window = std::make_shared<sf::RenderWindow>();
	context->graphicsManager = std::make_shared<GraphicsManager>(window);

	context->inputManager = std::make_shared<InputManager>();
	context->physicsManager = std::make_shared<PhysicsManager>();

	context->gameplayManager->loadMap(startMap);

	sf::Clock clock;
	while (running)
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event event;
		while (window->pollEvent(event))
		{
			onEvent(event);
		}
		
		context->graphicsManager->clear();
		context->graphicsManager->draw();
		context->gameplayManager->update();

		context->physicsManager->update();
		// physics::Manager::getInstance().update();
		context->graphicsManager->display();
		context->inputManager->clear();


		// Need Garbage Collector
		
		// gameplay::Manager::getInstance().garbageCollector();
		
		// for(auto actor : context->gameplayManager->getEntities())
		// {
		// 	delete actor;
		// }
	}
}

float Engine::getDeltaTime() const
{
	return deltaTime;
}

void Engine::onEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		running = false;
		break;
	case sf::Event::LostFocus:
		context->inputManager->setActive(false);
		break;

	case sf::Event::GainedFocus:
		context->inputManager->setActive(true);
		break;
	case sf::Event::KeyPressed:
		context->inputManager->onKeyPressed(event.key);
		break;

	case sf::Event::KeyReleased:
		context->inputManager->onKeyReleased(event.key);
		break;
	default:
		break;
	}
}

void Engine::exit()
{
	running = false;
}

Context& Engine::getContext()
{
	if (!context)
	{
		context = new Context();
	}
	return *context;
}

Engine &Engine::getInstance()
{
	if (!instance)
		instance = new Engine();

	return *instance;
}