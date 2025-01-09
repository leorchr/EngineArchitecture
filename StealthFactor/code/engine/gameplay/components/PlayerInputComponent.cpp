#include "PlayerInputComponent.h"
#include "engine/gameplay/entities/Player.hpp"
#include "engine/input/InputManager.hpp"
#include "engine/gameplay/GameplayManager.hpp"
#include <SFML/Window/Keyboard.hpp>

PlayerInputComponent::PlayerInputComponent(Entity& entityP) : InputComponent(entityP)
{
	player = dynamic_cast<Player*>(&entity);
}
PlayerInputComponent::~PlayerInputComponent() {}

void PlayerInputComponent::update()
{
	InputComponent::update();

	justMoved = false;
	auto position = player->getPosition();
	float rotation = player->getRotation();
	if (inputManager->isKeyJustPressed(sf::Keyboard::Left))
	{
		justMoved = true;
		position.x -= GameplayManager::CELL_SIZE;
		rotation = 180.f;
	}
	if (inputManager->isKeyJustPressed(sf::Keyboard::Right))
	{
		justMoved = true;
		position.x += GameplayManager::CELL_SIZE;
		rotation = 0.f;
	}
	
	if (inputManager->isKeyJustPressed(sf::Keyboard::Up))
	{
		justMoved = true;
		position.y -= GameplayManager::CELL_SIZE;
		rotation = -90.f;
	}
	
	if (inputManager->isKeyJustPressed(sf::Keyboard::Down))
	{
		justMoved = true;
		position.y += GameplayManager::CELL_SIZE;
		rotation = 90.f;
	}
	if (justMoved)
	{
		player->setPosition(position);
		player->setRotation(rotation);
	}
}