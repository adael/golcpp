#include <SFML/Graphics.hpp>
#include <vector>
#include "Grid.h"
#include "State.h"
#include "Controller.h"

int main()
{

	auto sw = 1920;
	auto sh = 1080;
	auto padding = 10;
	auto size = 15;
	auto cols = (sw - padding * 2) / size;
	auto rows = (sh - padding * 2) / size;
	bool paused = true;

	sf::RenderWindow window(sf::VideoMode(sw, sh), "Game Of Life", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	Grid grid(cols, rows, size);
	grid.showInnerGrid(true);
	grid.setPosition(padding, padding);

	State state(cols, rows);
	Controller controller;

	while (window.isOpen())
	{

		controller.handle(window);
		
		if(controller.close_requested){
			window.close();
			return 0;
		}

		if(paused && controller.mouse_clicked){
			if (grid.isPositionInBounds(controller.mouse_click_position)) {
				sf::Vector2i cellPos = grid.getCellPositionAt(controller.mouse_click_position);
				if(controller.mouse_left_button_clicked){
					state.setAlive(cellPos);
				}else if(controller.mouse_right_button_clicked){
					state.setDead(cellPos);
				}
			}
		}

		if (controller.space_pressed) {
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