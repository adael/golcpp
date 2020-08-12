#include "State.h"

State::State(short cols, short rows)
{
	this->cols = cols;
	this->rows = rows;
	this->state.resize(cols * rows);
	this->newState = this->state;
}

bool State::isAlive(sf::Vector2i pos) const
{
	auto index = getIndex(pos);
	if (index < 0 || index >= state.size()) {
		return false;
	}
	else {
		return state[index];
	}
}

void State::setAlive(sf::Vector2i pos)
{
	newState[getIndex(pos)] = true;
}

void State::setDead(sf::Vector2i pos)
{
	newState[getIndex(pos)] = false;
}

sf::Uint8 State::countAliveNeighbours(sf::Vector2i pos) const
{
	return
		isAlive(sf::Vector2i(pos.x - 1, pos.y - 1))
		+ isAlive(sf::Vector2i(pos.x, pos.y - 1))
		+ isAlive(sf::Vector2i(pos.x + 1, pos.y - 1))
		+ isAlive(sf::Vector2i(pos.x - 1, pos.y))
		+ isAlive(sf::Vector2i(pos.x + 1, pos.y))
		+ isAlive(sf::Vector2i(pos.x - 1, pos.y + 1))
		+ isAlive(sf::Vector2i(pos.x, pos.y + 1))
		+ isAlive(sf::Vector2i(pos.x + 1, pos.y + 1));
}

void State::tick()
{
	newState = state;
	for (sf::Uint8 x = 0; x < cols; x++) {
		for (sf::Uint8 y = 0; y < rows; y++) {
			auto pos = sf::Vector2i(x, y);
			auto vecinos = countAliveNeighbours(pos);

			if (vecinos == 3) {
				setAlive(pos);
			}
			else if (vecinos < 2 || vecinos > 3) {
				setDead(pos);
			}
		}
	}
}
void State::consolidate() 
{
	state = newState;
}

std::vector<sf::Vector2i> State::getAliveCells() const
{
	auto cells = std::vector<sf::Vector2i>();
	for (sf::Uint8 x = 0; x < cols; x++) {
		for (sf::Uint8 y = 0; y < rows; y++) {
			sf::Vector2i pos(x, y);
			if (isAlive(pos) == true) {
				cells.push_back(pos);
			}
		}
	}
	return cells;
}

sf::Uint32 State::getIndex(sf::Vector2i pos) const
{
	return pos.x + (pos.y * cols);
}
