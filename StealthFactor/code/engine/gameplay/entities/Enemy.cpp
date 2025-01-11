#include "Enemy.hpp"

#include "engine/Engine.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include "engine/gameplay/components/ShapeComponent.h"
#include "engine/gameplay/entities/Player.hpp"

#include <pugixml/pugixml.hpp>
#include <iostream>
#include <sstream>


Enemy::Enemy(const std::string &archetypeName)
{
	gameplayManager = Engine::getInstance().getContext().gameplayManager;
	loadArchetype(archetypeName);
}

Enemy::~Enemy() {}

void Enemy::update()
{
	auto &player = gameplayManager->getPlayer();
	if (player.hasJustMoved())
	{
		auto &playerPosition = player.getPosition();
		auto &myPosition = getPosition();
	
		auto offset = myPosition - playerPosition;
		offset /= GameplayManager::CELL_SIZE;
		float distance2 = offset.x * offset.x + offset.y * offset.y;
		if (distance2 <= visionRadius * visionRadius)
		{
			if (shootDelayCounter < shootDelay)
			{
				++shootDelayCounter;
			}
			else
			{
				gameplayManager->gameOver();
			}
		}
		else
		{
			shootDelayCounter = 0;
		}
	}
}

void Enemy::loadArchetype(const std::string &archetypeName)
{
	std::stringstream filename;
	filename << "archetypes/" << archetypeName << ".xml";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

	if (result)
	{
		assert(!doc.empty());
		auto xmlArchetype = doc.first_child();

		std::string shapeListName = xmlArchetype.child_value("shapelist");
		shapeComp = std::make_shared<ShapeComponent>(*this, shapeListName);

		visionRadius = std::stof(xmlArchetype.child_value("vision_radius"));
		assert(visionRadius > 0.f);

		shootDelay = std::stoi(xmlArchetype.child_value("shoot_delay"));
		assert(shootDelay >= 0);
	}
	else
	{
		std::cerr << "Archetype [" << archetypeName << "] parsed with errors." << std::endl;
		std::cerr << "Error description: " << result.description() << std::endl;
		std::cerr << "Error offset: " << result.offset << std::endl;
	}
}
