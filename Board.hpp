#pragma once

#include "Field.hpp"

#include <array>
#include <vector>
#include <memory>

class Board : public sf::Drawable {
public:
	Board(sf::Font& font);
	~Board() = default;

	std::array<std::array<std::shared_ptr<Field>, 10>, 10> listOfFieldsForFirstPlayer;
	std::array<std::array<std::shared_ptr<Field>, 10>, 10> listOfFieldsForSecondPlayer;
	std::vector<std::shared_ptr<sf::Text>> listOfOtherFields;

	void createBoard(sf::Font & font);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (int i = 0; i < listOfOtherFields.size(); i++)
			target.draw(*listOfOtherFields[i], states);
		for(int i = 0; i< 10;i++)
			for (int j = 0; j < 10; j++) {
				target.draw(*listOfFieldsForFirstPlayer[i][j]->field, states);
				target.draw(*listOfFieldsForSecondPlayer[i][j]->field, states);
			}
	}
};

