#pragma once

#include <set>
#include <vector>
#include <ode/collision.h>

class PhysicsManager
{
public:

	
	struct Collision
	{
		dGeomID o1;
		dGeomID o2;

		Collision(dGeomID o1, dGeomID o2);
	};

	using Collisions = std::vector<Collision>;

	PhysicsManager();
	~PhysicsManager();

	void update();
	void clear();

	dSpaceID getSpaceId() const;
	void setSpaceId(dSpaceID newSpaceId);

	std::set<dGeomID> getCollisionsWith(dGeomID object) const;

private:
	dSpaceID spaceId;
	Collisions frameCollisions;

	static void nearCallback(void *data, dGeomID o1, dGeomID o2);
};
