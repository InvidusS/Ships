#include "Game.hpp"
#include "Board.hpp"

#include <Windows.h>

Game::Game() {
	window.create(sf::VideoMode(1350, 800), "Ships", sf::Style::None | sf::Style::Titlebar);
	
	board = std::make_shared<Board>(font);

	font.loadFromFile("arial.ttf");

	turnText.setString("Ship Battle!");
	turnText.setFont(font);
	turnText.setFillColor(sf::Color::White);
	turnText.setCharacterSize(25);
	turnText.setPosition(100, 650);

	timerText.setString('0');
	timerText.setFont(font);
	timerText.setFillColor(sf::Color::White);
	timerText.setCharacterSize(25);
	timerText.setPosition(100, 700);

	sf::Clock timer;
	timer.restart();

	while (window.isOpen()) {
		window.clear();

		sf::Event evt;
		sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		if (!checkWinLose(player1) && !checkWinLose(player2)) {
			if (turn) {
				turnText.setString("Player 1 turn...");
			}
			else {
				turnText.setString("Player 2 turn...");
			}

			timerText.setString(std::to_string(static_cast<int>(timer.getElapsedTime().asSeconds())));
		}

		

		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::MouseButtonReleased:
				switch (evt.mouseButton.button) {
				case sf::Mouse::Left:
					if (setting)
						setShips();
					else {
						if (!checkWinLose(player1) && !checkWinLose(player2)) {
							if (turn)
								shot(player1);
							else
								shot(player2);
						}
					}
					break;

				case sf::Mouse::Right:
					rotation = !rotation;
					break;
				}
				break;

			case sf::Event::KeyReleased:
				switch (evt.key.code) {
				case sf::Keyboard::Num1:
					if (shipLeft[turn][1] > 0)
						playerShipLength[turn] = 1;
					break;

				case sf::Keyboard::Num2:
					if (shipLeft[turn][2] > 0)
						playerShipLength[turn] = 2;
					break;

				case sf::Keyboard::Num3:
					if (shipLeft[turn][3] > 0)
						playerShipLength[turn] = 3;
					break;

				case sf::Keyboard::Num4:
					if (shipLeft[turn][4] > 0)
						playerShipLength[turn] = 4;
					break;

				case sf::Keyboard::Escape:
					window.close();
					break;
				}
				break;

			default:
				break;
			}
		}

		window.draw(*board);
		window.draw(turnText);
		window.draw(timerText);

		window.display();
	}
}

void Game::setShips() {
	auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	int x = 0;
	int y = 0;

	std::array<std::array<std::shared_ptr<Field>, 10>, 10>& curBoard = turn ? board->listOfFieldsForFirstPlayer : board->listOfFieldsForSecondPlayer;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (curBoard[i][j]->field->getGlobalBounds().contains(mousePosition)) {
				if (canBeOrCannotBeSet(i, j, curBoard)) {
					if (shipLeft[turn][playerShipLength[turn]] > 0) {
						x = i;
						y = j; 
						for (int k = 0; k < playerShipLength[turn]; k++) {
							if (!rotation)
								x = i + k;
							else
								y = j + k;

							curBoard[x][y]->field->setFillColor(sf::Color::Green);
							curBoard[x][y]->ship = true;
							curBoard[x][y]->shipSize = playerShipLength[turn];
						}
						shipLeft[turn][playerShipLength[turn]]--;

						if (shipLeft[turn][playerShipLength[turn]] == 0) {
							playerShipLength[turn] = 5;
							while (shipLeft[turn][--playerShipLength[turn]] <= 0 && playerShipLength[turn] > 0);
						}

						counter--;
						if (counter == 0)
							setting = false;
						turn = !turn;
					}
				}
			}
		}
	}
}

bool Game::canBeOrCannotBeSet(int cordX, int cordY, std::array<std::array<std::shared_ptr<Field>, 10>, 10>& curBoard) {
	bool canBeSetHere = true;
	int x = cordX;
	int y = cordY;

	if (!rotation) {
		if (x + playerShipLength[turn] > 10)
			return false;
	}
	else {
		if (y + playerShipLength[turn] > 10)
			return false;
	}
	if (canBeSetHere) {
		for (int i = 0; i < playerShipLength[turn]; i++) {
			if (!rotation) {
				x = cordX + i;
			}
			else {
				y = cordY + i; 
			}

			for (int j = (x - 1); j < (x + 2); j++) {
				for (int k = (y - 1); k < (y + 2); k++) {
					if (j >= 0 && j < 10 && k >= 0 && k < 10) {
						if (curBoard[j][k]->ship)
							canBeSetHere = false;
					}
				}
			}
		}
	}

	return canBeSetHere;
}

void Game::shot(int& score) {
	auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

	std::array<std::array<std::shared_ptr<Field>, 10>, 10>& curBoard = !turn ? board->listOfFieldsForFirstPlayer : board->listOfFieldsForSecondPlayer;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (curBoard[i][j]->field->getGlobalBounds().contains(mousePosition)) {
				if (!curBoard[i][j]->hit) {
					if (checkShot(curBoard[i][j]->number, curBoard)) {
						curBoard[i][j]->field->setFillColor(sf::Color::Red);
						score += 1;
						if (checkWinLose(score)) {
							if(turn)
								turnText.setString("Player 1 won!!!");
							else
								turnText.setString("Player 2 won!!!");
						}
					}
					else {
						curBoard[i][j]->field->setFillColor(sf::Color::Blue);
						turn = !turn;
					}
				}
			}
		}
	}
}

bool Game::checkShot(int number, std::array<std::array<std::shared_ptr<Field>, 10>, 10>& listOfFields) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (listOfFields[i][j]->number == number) {
				if (listOfFields[i][j]->ship) {
					listOfFields[i][j]->hit = true;
					return true;
				}
				else {
					listOfFields[i][j]->hit = true;
					return false;
				}
			}
		}
	}
}

bool Game::checkWinLose(int score) {
	return score == 20;
}