int turn = 0;
int click = 0;
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

    while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) { click = 1;}
			if (event.mouseButton.button == sf::Mouse::Right) { click = 2; }
			if (event.mouseButton.button == sf::Mouse::Middle) { click = 3; }
		}

		if (event.type == sf::Event::KeyPressed){

			if (event.key.code == sf::Keyboard::Escape){ window.close(); }

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

	window.clear();
	window.draw(background);
	Deck.drawOn(window);
	Wastepile.drawOn(window);
	Players[0].drawOn(window);
	Players[1].drawOn(window);

	window.display();

}

void switchTurn (NewHand Players[]) {
	turn++; if (turn > 1) {turn = 0;}
	if (turn == 0) {Players[0].show();Players[1].hide();}
	if (turn == 1) {Players[0].hide();Players[1].show();}

}


void thisTurn(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile) {

	NewHand &Player = Players[turn];
	int thisCard;

	if (click > 0) {thisCard = Player.hitbox(mousePosition);}

	if (click == 1) {
		if(Deck.hitbox(mousePosition)){ Player.addCard(Deck.grabCard()); }
		if(thisCard > -1){ Wastepile.addCard(Player.grabCard(thisCard)); }
	}
	if (click == 2) {
		if (thisCard > -1){ Player.bringToFront(thisCard); }
    }

    if (click == 3) {
		switchTurn(Players);
    }

}
