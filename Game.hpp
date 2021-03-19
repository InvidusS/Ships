#pragma once

#include "Field.hpp"
#include "Board.hpp"

#include <array>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class Game {
private:
	int player1 = 0;
	int player2 = 0;
	int counter = 20;
	bool turn = true;
	bool rotation = true;
	bool setting = true;

	std::map<bool, char> playerShipLength = {
		{true, 1},
		{false, 1}
	};

	std::map<bool, std::map<char, char>> shipLeft = {
		{true, {{1, 4}, {2, 3}, {3, 2}, {4, 1}}},
		{false, {{1, 4}, {2, 3}, {3, 2}, {4, 1}}}
	};

	sf::RenderWindow window;
	sf::Text turnText;
	sf::Text timerText;

	std::shared_ptr<Board> board = nullptr;

	void setShips();
	bool canBeOrCannotBeSet(int x, int y, std::array<std::array<std::shared_ptr<Field>, 10>, 10>& curBoard);
	void shot(int& score);
	bool checkShot(int number, std::array<std::array<std::shared_ptr<Field>, 10>, 10>& listOfFields);
	bool checkWinLose(int a);

public:
	Game();
	~Game() = default;

	sf::Font font;
};


