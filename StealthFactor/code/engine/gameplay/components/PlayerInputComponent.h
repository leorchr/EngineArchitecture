#pragma once
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(Entity& entityP);
	virtual ~PlayerInputComponent();
	void update() override;

private:
	class Player* player;
	bool justMoved{ false };
};
