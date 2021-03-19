#include "Game.hpp"
#include "Board.hpp"
#include "Field.hpp"

#include <SFML/Graphics.hpp>

Board::Board(sf::Font& font){
	createBoard(font);
}

void Board::createBoard(sf::Font& font) {
	float cordX = 102.0f;
	float cordY = 102.0f;
	int number = 1;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			auto field = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.0f, 50.0f));
			field->setOutlineColor(sf::Color::Black);
			field->setOutlineThickness(1.0f);
			field->setPosition(cordX, cordY);

			listOfFieldsForFirstPlayer[i][j] = std::make_shared<Field>(number++, false, false, field);
			cordX += 52;
		}
		cordX = 102.0f;
		cordY += 52;
	}

	cordX = 772.0f;
	cordY = 102.0f;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			auto field = std::make_shared<sf::RectangleShape>(sf::Vector2f(50.0f, 50.0f));
			field->setOutlineColor(sf::Color::Black);
			field->setOutlineThickness(1.0f);
			field->setPosition(cordX, cordY);

			listOfFieldsForSecondPlayer[i][j] = std::make_shared<Field>(number, false, false, field);
			cordX += 52;
			number++;
		}
		cordX = 772.0f;
		cordY += 52;
	}

	cordX = 120.0f;
	cordY = 50.0f;

	char c = 'A';

	for (int i = 0; i < 10; i++) {
		auto field = std::make_shared<sf::Text>();
		field->setString(std::to_string(i));
		field->setFillColor(sf::Color::White);
		field->setFont(font);
		field->setCharacterSize(25);
		field->setPosition(cordX, cordY);
		cordX += 52;
		listOfOtherFields.push_back(field);
	}

	cordX = 50.0f;
	cordY = 113.0f;

	for (int i = 0; i < 10; i++) {
		auto field = std::make_shared<sf::Text>();
		field->setString(c);
		field->setFillColor(sf::Color::White);
		field->setFont(font);
		field->setCharacterSize(25);
		field->setPosition(cordX, cordY);
		cordY += 52;
		listOfOtherFields.push_back(field);
		c++;
	}

	c = 'A';

	cordX = 790.0f;
	cordY = 50.0f;

	for (int i = 0; i < 10; i++) {
		auto field = std::make_shared<sf::Text>();
		field->setString(std::to_string(i));
		field->setFillColor(sf::Color::White);
		field->setFont(font);
		field->setCharacterSize(25);
		field->setPosition(cordX, cordY);
		cordX += 52;
		listOfOtherFields.push_back(field);
	}

	cordX = 720.0f;
	cordY = 113.0f;

	for (int i = 0; i < 10; i++) {
		auto field = std::make_shared<sf::Text>();
		field->setString(c);
		field->setFillColor(sf::Color::White);
		field->setFont(font);
		field->setCharacterSize(25);
		field->setPosition(cordX, cordY);
		cordY += 52;
		listOfOtherFields.push_back(field);
		c++;
	}
}
