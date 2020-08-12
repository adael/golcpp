#pragma once
#include "SFML/Graphics.hpp"

class Controller
{
public:
	Controller();

	void handle(sf::RenderWindow &window);
	bool close_requested = false;
	bool space_pressed = false;
	bool mouse_clicked = false;
	bool mouse_left_button_clicked = false;
	bool mouse_right_button_clicked = false;
	sf::Vector2i mouse_click_position;

};