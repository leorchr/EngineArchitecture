#pragma once

#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>

class Entity;

class Player;

class GameplayManager
{
public:	
	void update();

	void gameOver();

	sf::Vector2f getViewCenter() const;

	void loadMap(const std::string &mapName);
	void loadNextMap();

	const Player &getPlayer() const;
	void garbageCollector();
	std::set<Entity *> getEntities();

	static const float CELL_SIZE;

private:
	std::set<Entity *> entities{};
	Player *playerEntity{};

	// Map
	std::string currentMapName{};
	std::string nextMapName{};
	int rows{ 0 };
	int columns{ 0 };

	bool preventMapCompletion{ false };
	bool nextMapRequested{ false };
};