#include <iostream>
#include <fstream>
#include <vector>

int turn = 0;
int click = 0;
char dbgkey = 0;
bool windowResized = true;
sf::Vector2f mousePosition;
sf::Vector2i resolution(800,480);
std::vector <std::string> info;

void loadTextStrings() {
	std::ifstream textFile;
	textFile.open("./resources/txtstrings.txt");
	std::string toCopy;

	while(std::getline(textFile,toCopy)){
		info.push_back(toCopy);
	}

	textFile.close();

}

void tellUser(int line) {
	std::cout<<info[line]<<std::endl;
}

void playerInput(sf::Event &event, sf::RenderWindow &window){

	click = 0;
	dbgkey = 0;

    while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) { click = 1;}
			if (event.mouseButton.button == sf::Mouse::Right) { click = 2; }
			if (event.mouseButton.button == sf::Mouse::Middle) { click = 3; }
		}

		if (event.type == sf::Event::KeyPressed){

			if (event.key.code == sf::Keyboard::Escape){ window.close(); }
			if (event.key.code == sf::Keyboard::Num1){ dbgkey = '1'; }
			if (event.key.code == sf::Keyboard::Num2){ dbgkey = '2'; }

		}


		if (event.type == sf::Event::Resized) {
			sf::Vector2i lastPosition = window.getPosition();
			window.create(sf::VideoMode(window.getSize().x,window.getSize().y), info[0]);
			window.setPosition(lastPosition);
			windowResized = true;
		}
		if (event.type == sf::Event::Closed) {window.close();}
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

}

void drawOn(sf::RenderWindow &window, sf::Sprite &background, NewHand Players[], NewDeck &Deck, NewDeck &Wastepile){

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

	window.display();

}
