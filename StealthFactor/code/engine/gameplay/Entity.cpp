#include "Entity.hpp"
#include "components/Component.h"

const sf::Vector2f & Entity::getPosition() const
{
	return _position;
}

void Entity::setPosition(const sf::Vector2f &newPosition)
{
	_position = newPosition;
	updateTransform();
}

float Entity::getRotation() const
{
	return _rotation;
}

void Entity::setRotation(float newRotation)
{
	_rotation = newRotation;
	updateTransform();
}

void Entity::addComponent(std::shared_ptr<Component> component)
{
	if(component) components.push_back(component);
}

void Entity::removeComponent(std::shared_ptr<Component> component)
{
	auto it = std::find(components.begin(), components.end(), component);
	if(it != components.end())
	{
		components.erase(it);
	}
}

const sf::Transform & Entity::getTransform() const
{
	return _transform;
}

void Entity::updateTransform()
{
	_transform = sf::Transform::Identity;
	_transform.translate(_position);
	_transform.rotate(_rotation);
}
