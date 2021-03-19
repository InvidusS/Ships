#pragma once

#include <SFML/Graphics.hpp>

class Field : public sf::Drawable {
public:
	Field(int number, bool hit, bool ship, std::shared_ptr<sf::RectangleShape> field);
	~Field() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(*field, states);
    }

	int shipSize = 0;
	int number;
	bool hit;
	bool ship;

	std::shared_ptr<sf::RectangleShape> field; 
};


