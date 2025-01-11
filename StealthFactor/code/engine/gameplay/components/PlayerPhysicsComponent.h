#pragma once
#include "PhysicsComponent.h"

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    PlayerPhysicsComponent(Entity& entity);
    virtual ~PlayerPhysicsComponent() override;

    virtual void update() override;

protected:
    class Player* player;
    struct Context* context;
};

