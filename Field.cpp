#include "Field.hpp"

Field::Field(int number, bool hit, bool ship, std::shared_ptr<sf::RectangleShape> field) : number(number), hit(hit), ship(ship), field(field) {}