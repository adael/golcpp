#include <SFML/Graphics.hpp>
#include <vector>
#include "Grid.h";
#include "State.h";
#include "main.h"

int main()
{

	auto sw = 1000;
	auto sh = 1000;
	auto padding = 20;
	auto size = 20;
	auto cols = (sw - padding * 2) / size;
	auto rows = (sh - padding * 2) / size;
	bool paused = false;

	sf::RenderWindow window(sf::VideoMode(sw, sh), "Game Of Life");

	Grid grid(rows, cols, size);
	grid.showInnerGrid(true);
	grid.setPosition(padding, padding);

	State state(rows, cols);

	while (window.isOpen())
	{
		sf::Event event;
		
		bool space_pressed = false;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					space_pressed = true;
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (grid.isPositionInBounds(localPosition)) {
					sf::Vector2i cellPos = grid.getCellPositionAt(localPosition);
					state.setAlive(cellPos);
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (grid.isPositionInBounds(localPosition)) {
					sf::Vector2i cellPos = grid.getCellPositionAt(localPosition);
					state.setDead(cellPos);
				}
			}
		}

		if (space_pressed) {
			paused = !paused;
		}

		grid.showInnerGrid(paused);

		if (!paused) {
			state.tick();
		}
		state.consolidate();
		grid.setAliveCells(state.getAliveCells());

		window.clear();
		window.draw(grid);
		window.display();
	}

	return 0;
}