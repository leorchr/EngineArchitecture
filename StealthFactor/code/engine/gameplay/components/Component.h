#pragma once
#include <memory>

class Component : public std::enable_shared_from_this<Component>
{
public:
	Component(class Entity& entity);
	virtual ~Component();
	Entity* getEntity();

protected:
	class Entity& entity;
};