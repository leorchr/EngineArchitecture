#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/Transform.hpp>

namespace sf {
	class RenderWindow;
}

class Entity
{
public:
	virtual ~Entity() =default;

	virtual void update() = 0;

	const sf::Vector2f &getPosition() const;
	void setPosition(const sf::Vector2f &newPosition);

	float getRotation() const;
	void setRotation(float newRotation);

	const sf::Transform &getTransform() const;
	bool isDead = false;

private:
	sf::Vector2f _position{};
	float _rotation{ 0.f };
	sf::Transform _transform;
	void updateTransform();
};
