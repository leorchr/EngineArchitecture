#pragma once
#include <ode/common.h>
#include <ode/collision.h>
#include "engine/gameplay/components/Component.h"


class PhysicsComponent : public Component
{
public:
    PhysicsComponent(Entity& entity);
    virtual ~PhysicsComponent();

    virtual void update();
    bool isValid() const;

protected:
    dGeomID collisionGeomId;
};

