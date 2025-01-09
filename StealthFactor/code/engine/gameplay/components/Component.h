#pragma once
#include <memory>

class Component : public std::enable_shared_from_this<Component>
{
public:
	Component(class Entity& entity);
	virtual ~Component();
	void initialize();

protected:
	class Entity& entity;
};