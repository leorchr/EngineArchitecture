#include "InputComponent.h"
#include "engine/Engine.hpp"
#include "engine/gameplay/Entity.hpp"
#include "engine/input/InputManager.hpp"
#include <memory>

InputComponent::InputComponent(Entity& entityP) : Component(entityP)
{
	inputManager = Engine::getInstance().getContext().inputManager;
}

InputComponent::~InputComponent() {}

void InputComponent::update() {}