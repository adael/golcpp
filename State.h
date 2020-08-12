#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class State
{
public:
	
	State(short cols, short rows);

	bool isAlive(sf::Vector2i pos) const;
	sf::Uint8 countAliveNeighbours(sf::Vector2i pos) const;
	std::vector<sf::Vector2i> getAliveCells() const;
	void setAlive(sf::Vector2i pos);
	void setDead(sf::Vector2i  pos);
	void tick();
	void consolidate();


private:

	sf::Uint32 getIndex(sf::Vector2i pos) const;

	short rows;
	short cols;

	std::vector<bool> state;
	std::vector<bool> newState;
	sf::SoundBuffer buffer;
	sf::Sound sound;

};

