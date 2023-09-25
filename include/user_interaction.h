#include <iostream>
#include <fstream>
#include <vector>

int turn = 0;
int click = 0;
char fn = 0;
bool windowResized = true;
sf::Vector2f mousePosition;
sf::Vector2i resolution(800,480);

void playerInput(sf::Event &event, sf::RenderWindow &window, GameUI &UserInterface){

	click = 0;
	fn = 0;

    while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) { click = 1;}
			if (event.mouseButton.button == sf::Mouse::Right) { click = 2; }
			if (event.mouseButton.button == sf::Mouse::Middle) { click = 3; }
		}

		if (event.type == sf::Event::KeyPressed){

			if (event.key.code == sf::Keyboard::Escape){ window.close(); }
			if (event.key.code == sf::Keyboard::F1){ fn = '1'; }
			if (event.key.code == sf::Keyboard::F2){ fn = '2'; }

		}


		if (event.type == sf::Event::Resized) {
			sf::Vector2i lastPosition = window.getPosition();
			window.create(sf::VideoMode(window.getSize().x,window.getSize().y), "");
			window.setPosition(lastPosition);
			windowResized = true;
		}
		if (event.type == sf::Event::Closed) {window.close();}
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

	UserInterface.hitbox(mousePosition,click);
	if (UserInterface.event == 4) { window.close(); }

}

void drawOn(sf::RenderWindow &window, sf::Sprite &background, NewHand Players[], NewDeck &Deck, NewDeck &Wastepile, GameUI &UserInterface){

	if (windowResized) {
		background.setScale(
		window.getSize().x / background.getLocalBounds().width,
		window.getSize().y / background.getLocalBounds().height
		);

		Wastepile.refreshPos(window);
		Deck.refreshPos(window);
		Players[0].refreshPos(window);
		Players[1].refreshPos(window);
		windowResized = false;

	}

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

	window.clear();
	window.draw(background);
	Deck.drawOn(window);
	Wastepile.drawOn(window);
	Players[0].drawOn(window);
	Players[1].drawOn(window);
	UserInterface.drawOn(window);

}
