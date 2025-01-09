#pragma once
#include <memory>
#include <vector>
#include <SFML/Config.hpp>

class ShapeList;
namespace sf
{
	class RenderWindow;
	
}

class GraphicsManager
{
public:
	GraphicsManager(std::shared_ptr<sf::RenderWindow> window);
	~GraphicsManager();

	void update();

	void clear();
	void draw();
	void display();

	void addShape(class ShapeComponent* shapeComponent);
	void removeShape(class ShapeComponent* shapeComponent);

	bool hasFocus() const;

private:
	std::shared_ptr<sf::RenderWindow> sharedWindow;
	std::shared_ptr<class GameplayManager> gm;

	std::vector<class ShapeComponent*> shapesToDraw;

	static const sf::Int16 WINDOW_WIDTH = 800;
	static const sf::Int16 WINDOW_HEIGHT = 600;
};