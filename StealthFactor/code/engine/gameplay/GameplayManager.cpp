#include "engine/gameplay/GameplayManager.hpp"

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <pugixml/pugixml.hpp>
#include <engine/Engine.hpp>
#include <engine/gameplay/entities/Enemy.hpp>
#include <engine/gameplay/entities/Player.hpp>
#include <engine/gameplay/entities/Target.hpp>
#include <engine/gameplay/Entity.hpp>

#include "engine/physics/PhysicsManager.hpp"

const float GameplayManager::CELL_SIZE = 50.f;

void GameplayManager::update()
{
	for (auto entity : entities)
	{
		if(!entity->isDead) entity->update();
	}
	preventMapCompletion = false;
	if (nextMapRequested && !nextMapName.empty())
	{
		nextMapRequested = false;
		loadMap(nextMapName);
	}
}

void GameplayManager::gameOver()
{
	std::cout << "Game over" << std::endl;
	Engine::getInstance().getContext().physicsManager->setSpaceId(dHashSpaceCreate(0));
	loadMap(currentMapName);
}

sf::Vector2f GameplayManager::getViewCenter() const
{
	return sf::Vector2f{ columns * (CELL_SIZE / 2.f), rows * (CELL_SIZE / 2.f) };
}

void GameplayManager::loadMap(const std::string & mapName)
{
	for (auto entity : entities)
	{
		entity->isDead = true;
	}

	std::stringstream filename;
	filename << "maps/" << mapName << ".xml";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

	if (result)
	{
		assert(!doc.empty());
		auto xmlMap = doc.first_child();

		rows = std::stoi(xmlMap.child_value("rows"));
		assert(rows >= 0);

		columns = std::stoi(xmlMap.child_value("columns"));
		assert(columns >= 0);

		for (auto &xmlElement : xmlMap.child("elements").children())
		{
			if (!std::strcmp(xmlElement.name(), "enemy"))
			{
				int row = std::stoi(xmlElement.child_value("row"));
				assert(row >= 0 && row < rows);

				int column = std::stoi(xmlElement.child_value("column"));
				assert(column >= 0 && column < columns);

				std::string archetypeName = xmlElement.child_value("archetype");

				auto entity = new Enemy{ archetypeName };
				entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

				entities.insert(entity);
			}

			if (!std::strcmp(xmlElement.name(), "target"))
			{
				int row = std::stoi(xmlElement.child_value("row"));
				assert(row >= 0 && row < rows);

				int column = std::stoi(xmlElement.child_value("column"));
				assert(column >= 0 && column < columns);

				auto entity = new Target{};
				entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

				entities.insert(entity);
			}
			if (!std::strcmp(xmlElement.name(), "player"))
			{
				int row = std::stoi(xmlElement.child_value("row"));
				assert(row >= 0 && row < rows);

				int column = std::stoi(xmlElement.child_value("column"));
				assert(column >= 0 && column < columns);

				auto entity = new Player{};
				entity->setPosition(sf::Vector2f{ (column + 0.5f) * CELL_SIZE, (row + 0.5f) * CELL_SIZE });

				entities.insert(entity);
				playerEntity = entity;
			}

		}

		currentMapName = mapName;
		nextMapName = xmlMap.child_value("next_map");

		// JIRA-1337: Map is skipped.
		// This prevents the map to be completed during the first frame. I don't know why this happens.
		preventMapCompletion = true;
	}
	else
	{
		std::cerr << "Map [" << mapName << "] parsed with errors." << std::endl;
		std::cerr << "Error description: " << result.description() << std::endl;
		std::cerr << "Error offset: " << result.offset << std::endl;
	}
}

void GameplayManager::loadNextMap()
{
	if (!preventMapCompletion)
	{
		nextMapRequested = true;
		Engine::getInstance().getContext().physicsManager->setSpaceId(dHashSpaceCreate(0));
	}
}

const Player &GameplayManager::getPlayer() const
{
	assert(playerEntity);
	return *playerEntity;
}

void GameplayManager::garbageCollector()
{
	for (auto it = entities.begin(); it != entities.end(); )
    {
        if ((*it)->isDead)
        {
        	delete *it;
            it = entities.erase(it); // Retourne le nouvel itérateur après la suppression
        }
        else
        {
            ++it; // Passe au suivant si aucune suppression
        }
    }
}

std::set<Entity*> GameplayManager::getEntities()
{
	return entities;
}