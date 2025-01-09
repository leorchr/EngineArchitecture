#pragma once
#include <engine/gameplay/entities/Character.hpp>

class Player : public Character
{
public:
	Player();
	virtual void update() override;
	bool hasJustMoved() const;

private:
	bool justMoved{ false };

	std::shared_ptr<class PlayerInputComponent> inputComp;
};