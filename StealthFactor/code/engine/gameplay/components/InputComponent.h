#pragma once
#include "Component.h"
#include <memory>

class InputComponent : public Component
{
public:
	InputComponent(class Entity& entity);
	virtual ~InputComponent();
	virtual void update();
	
protected:
	std::shared_ptr<class InputManager> inputManager;
};