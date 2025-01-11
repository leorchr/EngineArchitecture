#pragma once
#include "engine/gameplay/entities/Character.hpp"

class Player : public Character
{
public:
	Player();
	virtual void update() override;
	bool hasJustMoved() const;
	void setJustMoved(bool pJustMoved);

private:
	bool justMoved{ false };

	std::shared_ptr<class PlayerInputComponent> inputComp;
	std::shared_ptr<class PlayerPhysicsComponent> physicsComponent;
	
	struct Context* context;
};