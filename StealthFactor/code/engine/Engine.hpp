#pragma once

#include <string>
#include <memory>
#include <SFML/Window/Event.hpp>

struct Context
{
	std::shared_ptr<class GraphicsManager> graphicsManager;
	std::shared_ptr<class GameplayManager> gameplayManager;
	std::shared_ptr<class InputManager> inputManager;
};


class Engine
{
public:
	void loadConfiguration();

	void run();
	float getDeltaTime() const;
	void onEvent(const sf::Event &event);
	void exit();
	
	Context& getContext();

	static Engine &getInstance();

private:
	bool running;
	float deltaTime;

	Context* context;

	// Configuration
	std::string startMap;

	static Engine *instance;
};
