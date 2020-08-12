#include "Controller.h"

Controller::Controller() {

}

void Controller::handle(sf::RenderWindow &window)
{
	sf::Event event;
	
	close_requested = false;
	space_pressed = false;
	mouse_clicked = false;
	mouse_left_button_clicked = false;
	mouse_right_button_clicked = false;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			close_requested = true;
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Space) {
				space_pressed = true;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			mouse_clicked = true;
			mouse_left_button_clicked = true;
			mouse_click_position = sf::Mouse::getPosition(window);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			mouse_clicked = true;
			mouse_right_button_clicked = true;
			mouse_click_position = sf::Mouse::getPosition(window);
		}
	}
}